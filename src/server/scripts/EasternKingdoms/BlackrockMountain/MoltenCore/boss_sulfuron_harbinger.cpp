/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
SDName: Boss_Sulfuron_Harbringer
SD%Complete: 80
SDComment: Adds NYI
SDCategory: Molten Core
EndScriptData */

#include "molten_core.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"


enum Spells
{
    // Sulfuron Harbringer
    SPELL_DARK_STRIKE           = 19777,
    SPELL_DEMORALIZING_SHOUT    = 19778,
    SPELL_INSPIRE               = 19779,
    SPELL_KNOCKDOWN             = 19780,
    SPELL_FLAMESPEAR            = 19781,

    // Adds
    SPELL_HEAL                  = 19775,
    SPELL_SHADOWWORDPAIN        = 19776,
    SPELL_IMMOLATE              = 20294,
};

enum Events
{
    EVENT_DARK_STRIKE           = 1,
    EVENT_DEMORALIZING_SHOUT,
    EVENT_INSPIRE,
    EVENT_KNOCKDOWN,
    EVENT_FLAMESPEAR,

    EVENT_HEAL,
    EVENT_SHADOW_WORD_PAIN,
    EVENT_IMMOLATE,
};

class boss_sulfuron : public CreatureScript
{
public:
    boss_sulfuron() : CreatureScript("boss_sulfuron")
    {
    }

    struct boss_sulfuronAI : public BossAI
    {
        boss_sulfuronAI(Creature* creature) : BossAI(creature, BOSS_SULFURON_HARBINGER)
        {
        }

        void EnterCombat(Unit* /*victim*/) override
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_DARK_STRIKE, urand(4000, 7000));
            events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, urand(6000, 20000));
            events.ScheduleEvent(EVENT_INSPIRE, urand(7000, 10000));
            events.ScheduleEvent(EVENT_KNOCKDOWN, 6000);
            events.ScheduleEvent(EVENT_FLAMESPEAR, 2000);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
            {
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
            {
                return;
            }

            while (uint32 const eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DARK_STRIKE:
                    {
                        DoCastSelf(SPELL_DARK_STRIKE);
                        events.RepeatEvent(urand(4000, 7000));
                        break;
                    }
                    case EVENT_DEMORALIZING_SHOUT:
                    {
                        DoCastVictim(SPELL_DEMORALIZING_SHOUT);
                        events.RepeatEvent(urand(12000, 18000));
                        break;
                    }
                    case EVENT_INSPIRE:
                    {
                        std::list<Creature*> healers = DoFindFriendlyMissingBuff(45.0f, SPELL_INSPIRE);
                        if (!healers.empty())
                        {
                            DoCast(acore::Containers::SelectRandomContainerElement(healers), SPELL_INSPIRE);
                        }

                        DoCastSelf(SPELL_INSPIRE);
                        events.RepeatEvent(urand(13000, 20000));
                        break;
                    }
                    case EVENT_KNOCKDOWN:
                    {
                        DoCastVictim(SPELL_KNOCKDOWN);
                        events.RepeatEvent(urand(10000, 20000));
                        break;
                    }
                    case EVENT_FLAMESPEAR:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        {
                            DoCast(target, SPELL_FLAMESPEAR);
                        }
                        events.RepeatEvent(urand(12000, 16000));
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetMoltenCoreAI<boss_sulfuronAI>(creature);
    }
};

class npc_flamewaker_priest : public CreatureScript
{
public:
    npc_flamewaker_priest() : CreatureScript("npc_flamewaker_priest") { }

    struct npc_flamewaker_priestAI : public ScriptedAI
    {
        npc_flamewaker_priestAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset() override
        {
            events.Reset();
        }

        void JustDied(Unit* /*killer*/) override
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*victim*/) override
        {
            events.ScheduleEvent(EVENT_HEAL, urand(15000, 30000));
            events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, urand(2000, 4000));
            events.ScheduleEvent(EVENT_IMMOLATE, urand(3500, 6000));
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
            {
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
            {
                return;
            }

            while (uint32 const eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_HEAL:
                    {
                        if (Unit* target = DoSelectLowestHpFriendly(60.0f, 1))
                        {
                            DoCast(target, SPELL_HEAL);
                        }
                        events.RepeatEvent(urand(15000, 20000));
                        break;
                    }
                    case EVENT_SHADOW_WORD_PAIN:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_SHADOWWORDPAIN))
                        {
                            DoCast(target, SPELL_SHADOWWORDPAIN);
                        }
                        events.RepeatEvent(urand(2500, 5000));
                        break;
                    }
                    case EVENT_IMMOLATE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_IMMOLATE))
                        {
                            DoCast(target, SPELL_IMMOLATE);
                        }
                        events.RepeatEvent(urand(5000, 7000));
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetMoltenCoreAI<npc_flamewaker_priestAI>(creature);
    }
};

void AddSC_boss_sulfuron()
{
    new boss_sulfuron();
    new npc_flamewaker_priest();
}
