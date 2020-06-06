DELETE FROM `command` WHERE `name`='qs';

INSERT INTO `command` (`name`, `security`, `help`) VALUES
('qs', 1, 'Syntax: .qs #questID It allows the moderator, to know the status of a mission of a player or own, through the id.');
