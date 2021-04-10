/*
 * Originally written by Xinef - Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#ifndef DEF_OLD_HILLSBRAD_H
#define DEF_OLD_HILLSBRAD_H

#include "CreatureAIImpl.h"

#define OldHillsbradScriptName "instance_old_hillsbrad"

enum DataIds
{
    DATA_ESCORT_PROGRESS    = 0,

    DATA_BOMBS_PLACED       = 10,
    DATA_THRALL_REPOSITION  = 11,
    DATA_THRALL_ADD_FLAG    = 12,
    DATA_THRALL_GUID        = 13,
    DATA_TARETHA_GUID       = 14,
    DATA_ATTEMPTS_COUNT     = 15
};

enum NpcIds
{
    NPC_EROZION             = 18723,
    NPC_THRALL              = 17876,
    NPC_TARETHA             = 18887,
    NPC_EPOCH_HUNTER        = 18096,
    NPC_LIEUTENANT_DRAKE    = 17848,

    NPC_LODGE_QUEST_TRIGGER = 20155,
    NPC_ORC_PRISONER        = 18598,

    NPC_DURNHOLDE_ARMORER   = 18764,
    NPC_DURNHOLDE_WARDEN    = 17833,
    NPC_DURNHOLDE_VETERAN   = 17860,
    NPC_DURNHOLDE_MAGE      = 17860,
    NPC_DURNHOLDE_SENTRY    = 17860,

    NPC_CAPTAIN_SKARLOC     = 17862,
    NPC_SKARLOC_MOUNT       = 18798,

    NPC_LORDAERON_SENTRY    = 17815,
    NPC_LORDAERON_WATCHMAN  = 17814,
};

enum GobjectIds
{
    GO_BARREL               = 182589,
    GO_ROARING_FLAME        = 182592,
    GO_PRISON_DOOR          = 184393
};

enum MiscIds
{
    QUEST_DIVERSION                 = 10283,
    WORLD_STATE_BARRELS_PLANTED     = 2436,
    SKARLOC_MOUNT_MODEL             = 18223,

    ENCOUNTER_PROGRESS_NONE             = 0,
    ENCOUNTER_PROGRESS_BARRELS          = 1,
    ENCOUNTER_PROGRESS_DRAKE_KILLED     = 2,
    ENCOUNTER_PROGRESS_THRALL_ARMORED   = 3,
    ENCOUNTER_PROGRESS_AMBUSHES_1       = 4,
    ENCOUNTER_PROGRESS_SKARLOC_KILLED   = 5,
    ENCOUNTER_PROGRESS_TARREN_MILL      = 6,
    ENCOUNTER_PROGRESS_TARETHA_MEET     = 7,
    ENCOUNTER_PROGRESS_EPOCH_KILLED     = 8,
    ENCOUNTER_PROGRESS_FINISHED         = 9,

    EVENT_INITIAL_BARRELS_FLAME     = 1,
    EVENT_FINAL_BARRELS_FLAME       = 2,
    EVENT_SUMMON_LIEUTENANT         = 3,
    EVENT_THRALL_REPOSITION         = 4,

    INSTANCE_POSITIONS_COUNT        = 3,
    THRALL_POSITIONS_COUNT          = 5
};

template <class AI, class T>
inline AI* GetOldHillsbradAI(T* obj)
{
    return GetInstanceAI<AI>(obj, OldHillsbradScriptName);
}

#endif
