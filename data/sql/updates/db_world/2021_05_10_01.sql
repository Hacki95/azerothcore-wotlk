-- DB update 2021_05_10_00 -> 2021_05_10_01
DROP PROCEDURE IF EXISTS `updateDb`;
DELIMITER //
CREATE PROCEDURE updateDb ()
proc:BEGIN DECLARE OK VARCHAR(100) DEFAULT 'FALSE';
SELECT COUNT(*) INTO @COLEXISTS
FROM information_schema.COLUMNS
WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'version_db_world' AND COLUMN_NAME = '2021_05_10_00';
IF @COLEXISTS = 0 THEN LEAVE proc; END IF;
START TRANSACTION;
ALTER TABLE version_db_world CHANGE COLUMN 2021_05_10_00 2021_05_10_01 bit;
SELECT sql_rev INTO OK FROM version_db_world WHERE sql_rev = '1620379730673714800'; IF OK <> 'FALSE' THEN LEAVE proc; END IF;
--
-- START UPDATING QUERIES
--

INSERT INTO `version_db_world` (`sql_rev`) VALUES ('1620379730673714800');

-- Adjust z-position of Feero Ironhand WP 29
UPDATE `waypoints` SET `position_z`=10.25865 WHERE `entry`=4484 AND `pointid`=29;

-- Adjust Feero Ironhand AI
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 4484;

DELETE FROM `smart_scripts` WHERE (`entryorguid` = 4484) AND (`source_type` = 0) AND (`id` IN (28, 29));
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_param4`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4484, 0, 28, 0, 10, 0, 100, 0, 1, 0, 0, 0, 0, 20, 1, 0, 0, 0, 0, 0, 9, 0, 0, 10, 0, 0, 0, 0, 0, 'Feero Ironhand - On OOC LOS - Auto attack'),
(4484, 0, 29, 0, 26, 0, 100, 0, 1, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 9, 0, 0, 10, 0, 0, 0, 0, 0, 'Feero Ironhand - On IC LOS - Auto attack');

--
-- END UPDATING QUERIES
--
COMMIT;
END //
DELIMITER ;
CALL updateDb();
DROP PROCEDURE IF EXISTS `updateDb`;
