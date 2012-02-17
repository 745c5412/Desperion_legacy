/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50508
Source Host           : localhost:3306
Source Database       : desperion

Target Server Type    : MYSQL
Target Server Version : 50508
File Encoding         : 65001

Date: 2012-02-17 18:23:28
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `accounts`
-- ----------------------------
DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `account` text NOT NULL,
  `password` text NOT NULL,
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `question` text NOT NULL,
  `answer` text NOT NULL,
  `pseudo` text NOT NULL,
  `logged` int(11) unsigned NOT NULL,
  `lastIP` text NOT NULL,
  `lastConnectionDate` bigint(18) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  `email` text NOT NULL,
  `ticket` text NOT NULL,
  `lastServer` int(11) NOT NULL DEFAULT '0',
  `subscriptionEnd` bigint(18) NOT NULL,
  `channels` text NOT NULL,
  `disallowed` text NOT NULL,
  `banEnd` bigint(18) NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=1212138004 DEFAULT CHARSET=latin1 AVG_ROW_LENGTH=81;

-- ----------------------------
-- Records of accounts
-- ----------------------------
INSERT INTO `accounts` VALUES ('jemoche', 'aae3e86ce2a2b28906e0db977262b860', '1', 'DELETE?', 'DELETE', 'ALEX', '0', '::ffff:127.0.0.1', '1326914579', '5', 'martin.alex32@hotmail.fr', '', '1', '4700000000000000000', '0,1,2,4,9,10,12,13', '', '0');
INSERT INTO `accounts` VALUES ('jemoche2', 'aae3e86ce2a2b28906e0db977262b860', '2', 'DELETE?', 'DELETE', 'TEST', '0', '::ffff:127.0.0.1', '1326561656', '5', 'martin.alex32@hotmail.fr', '', '1', '1', '0,1,2,4,5,9,10,12,13', '', '0');
INSERT INTO `accounts` VALUES ('jemoche3', 'aae3e86ce2a2b28906e0db977262b860', '3', 'DELETE?', 'DELETE', 'TEST2', '0', '::ffff:127.0.0.1', '1326561646', '5', 'martin.alex32@hotmail.fr', '', '1', '0', '', '', '0');

-- ----------------------------
-- Table structure for `account_social`
-- ----------------------------
DROP TABLE IF EXISTS `account_social`;
CREATE TABLE `account_social` (
  `guid` int(11) NOT NULL,
  `friends` text NOT NULL,
  `ennemies` text NOT NULL,
  `friendWarnOnConnection` tinyint(4) NOT NULL,
  `friendWarnOnLevelGain` tinyint(4) NOT NULL,
  `guildMemberWarnOnConnection` tinyint(4) NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of account_social
-- ----------------------------
INSERT INTO `account_social` VALUES ('1', '2,TEST;3,TEST2', '', '1', '1', '1');
INSERT INTO `account_social` VALUES ('2', '1,ALEX', '', '0', '0', '0');
INSERT INTO `account_social` VALUES ('3', '', '', '0', '0', '0');

-- ----------------------------
-- Table structure for `character_counts`
-- ----------------------------
DROP TABLE IF EXISTS `character_counts`;
CREATE TABLE `character_counts` (
  `accountGuid` int(11) NOT NULL,
  `serverId` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of character_counts
-- ----------------------------
INSERT INTO `character_counts` VALUES ('1', '1');
INSERT INTO `character_counts` VALUES ('2', '1');
INSERT INTO `character_counts` VALUES ('1', '1');
INSERT INTO `character_counts` VALUES ('3', '1');

-- ----------------------------
-- Table structure for `game_servers`
-- ----------------------------
DROP TABLE IF EXISTS `game_servers`;
CREATE TABLE `game_servers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `serverIp` text NOT NULL,
  `serverPort` int(11) NOT NULL,
  `state` int(11) NOT NULL DEFAULT '0',
  `playersLimit` int(11) NOT NULL,
  `key` text NOT NULL,
  `minLevel` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=20001 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of game_servers
-- ----------------------------
INSERT INTO `game_servers` VALUES ('1', '127.0.0.1', '5555', '1', '500', 'default', '0');
INSERT INTO `game_servers` VALUES ('7', '127.0.0.1', '5557', '1', '500', 'default', '0');

-- ----------------------------
-- Table structure for `ip_bans`
-- ----------------------------
DROP TABLE IF EXISTS `ip_bans`;
CREATE TABLE `ip_bans` (
  `ip` text NOT NULL,
  `banEnd` bigint(18) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ip_bans
-- ----------------------------
