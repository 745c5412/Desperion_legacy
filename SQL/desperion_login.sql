/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50508
Source Host           : localhost:3306
Source Database       : desperion

Target Server Type    : MYSQL
Target Server Version : 50508
File Encoding         : 65001

Date: 2011-10-08 21:56:13
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
  `lastConnectionDate` int(11) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  `email` text NOT NULL,
  `ticket` text NOT NULL,
  `lastServer` int(11) NOT NULL DEFAULT '0',
  `subscriptionEnd` int(11) NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=1212138003 DEFAULT CHARSET=latin1 AVG_ROW_LENGTH=81;

-- ----------------------------
-- Table structure for `account_bans`
-- ----------------------------
DROP TABLE IF EXISTS `account_bans`;
CREATE TABLE `account_bans` (
  `guid` int(11) unsigned NOT NULL,
  `banTime` bigint(18) NOT NULL,
  `banDate` bigint(18) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of account_bans
-- ----------------------------

-- ----------------------------
-- Table structure for `account_channels`
-- ----------------------------
DROP TABLE IF EXISTS `account_channels`;
CREATE TABLE `account_channels` (
  `guid` int(11) NOT NULL,
  `channels` text NOT NULL,
  `disallowed` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for `account_social`
-- ----------------------------
DROP TABLE IF EXISTS `account_social`;
CREATE TABLE `account_social` (
  `guid` int(11) NOT NULL,
  `friends` text NOT NULL,
  `ennemies` text NOT NULL,
  `ignored` text NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for `character_counts`
-- ----------------------------
DROP TABLE IF EXISTS `character_counts`;
CREATE TABLE `character_counts` (
  `accountGuid` int(11) NOT NULL,
  `serverID` int(11) NOT NULL,
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for `game_servers`
-- ----------------------------
DROP TABLE IF EXISTS `game_servers`;
CREATE TABLE `game_servers` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ServerIP` text NOT NULL,
  `ServerPort` int(11) NOT NULL,
  `State` int(11) NOT NULL DEFAULT '0',
  `PlayersLimit` int(11) NOT NULL,
  `Key` text NOT NULL,
  `MinLevel` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=20001 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for `ip_bans`
-- ----------------------------
DROP TABLE IF EXISTS `ip_bans`;
CREATE TABLE `ip_bans` (
  `IP` text NOT NULL,
  `banTime` bigint(18) NOT NULL,
  `banDate` bigint(18) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ip_bans
-- ----------------------------
