-- DB update 2021_06_18_11 -> 2021_06_18_12
DROP PROCEDURE IF EXISTS `updateDb`;
DELIMITER //
CREATE PROCEDURE updateDb ()
proc:BEGIN DECLARE OK VARCHAR(100) DEFAULT 'FALSE';
SELECT COUNT(*) INTO @COLEXISTS
FROM information_schema.COLUMNS
WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'version_db_world' AND COLUMN_NAME = '2021_06_18_11';
IF @COLEXISTS = 0 THEN LEAVE proc; END IF;
START TRANSACTION;
ALTER TABLE version_db_world CHANGE COLUMN 2021_06_18_11 2021_06_18_12 bit;
SELECT sql_rev INTO OK FROM version_db_world WHERE sql_rev = '1622479207694702700'; IF OK <> 'FALSE' THEN LEAVE proc; END IF;
--
-- START UPDATING QUERIES
--

INSERT INTO `version_db_world` (`sql_rev`) VALUES ('1622479207694702700');

UPDATE `command` SET `help` = 'Syntax: .character rename [$name] [reserveName]\r\n\r\nMark the character (selected in-game or with the $name argument) for rename at next login.\r\n\r\nIf [reserveName] is 1 then the player''s current name is added to the list of reserved names.' WHERE `command`.`name` = 'character rename';

--
-- END UPDATING QUERIES
--
UPDATE version_db_world SET date = '2021_06_18_12' WHERE sql_rev = '1622479207694702700';
COMMIT;
END //
DELIMITER ;
CALL updateDb();
DROP PROCEDURE IF EXISTS `updateDb`;
