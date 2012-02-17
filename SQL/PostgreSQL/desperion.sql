/*
Navicat PGSQL Data Transfer

Source Server         : postgreSQL
Source Server Version : 90102
Source Host           : localhost:5432
Source Database       : desperion
Source Schema         : public

Target Server Type    : PGSQL
Target Server Version : 90102
File Encoding         : 65001

Date: 2012-02-17 18:08:09
*/


-- ----------------------------
-- Table structure for "public"."account_social"
-- ----------------------------
DROP TABLE "public"."account_social";
CREATE TABLE "public"."account_social" (
"guid" int4 NOT NULL,
"friends" text NOT NULL,
"ennemies" text NOT NULL,
"friendWarnOnConnection" int2 NOT NULL,
"friendWarnOnLevelGain" int2 NOT NULL,
"guildMemberWarnOnConnection" int2 NOT NULL
)
WITH (OIDS=FALSE)

;

-- ----------------------------
-- Records of account_social
-- ----------------------------

-- ----------------------------
-- Table structure for "public"."accounts"
-- ----------------------------
DROP TABLE "public"."accounts";
CREATE TABLE "public"."accounts" (
"account" text NOT NULL,
"password" text NOT NULL,
"guid" int4 NOT NULL,
"question" text NOT NULL,
"answer" text NOT NULL,
"pseudo" text NOT NULL,
"logged" int4 NOT NULL,
"lastIp" text NOT NULL,
"lastConnectionDate" int8 NOT NULL,
"level" int2 DEFAULT 0 NOT NULL,
"email" text NOT NULL,
"ticket" text NOT NULL,
"subscriptionEnd" int8 NOT NULL,
"channels" text NOT NULL,
"disallowed" text NOT NULL,
"banEnd" int8 NOT NULL,
"lastServer" int4 DEFAULT 0 NOT NULL
)
WITH (OIDS=FALSE)

;

-- ----------------------------
-- Records of accounts
-- ----------------------------

-- ----------------------------
-- Table structure for "public"."character_counts"
-- ----------------------------
DROP TABLE "public"."character_counts";
CREATE TABLE "public"."character_counts" (
"accountGuid" int4 NOT NULL,
"serverId" int4 NOT NULL
)
WITH (OIDS=FALSE)

;

-- ----------------------------
-- Records of character_counts
-- ----------------------------

-- ----------------------------
-- Table structure for "public"."game_servers"
-- ----------------------------
DROP TABLE "public"."game_servers";
CREATE TABLE "public"."game_servers" (
"id" int4 NOT NULL,
"serverIp" text NOT NULL,
"serverPort" int4 NOT NULL,
"state" int4 DEFAULT 0 NOT NULL,
"playersLimit" int4 NOT NULL,
"key" text NOT NULL,
"minLevel" int4 NOT NULL
)
WITH (OIDS=FALSE)

;

-- ----------------------------
-- Records of game_servers
-- ----------------------------

-- ----------------------------
-- Table structure for "public"."ip_bans"
-- ----------------------------
DROP TABLE "public"."ip_bans";
CREATE TABLE "public"."ip_bans" (
"ip" text NOT NULL,
"banEnd" int8 NOT NULL
)
WITH (OIDS=FALSE)

;

-- ----------------------------
-- Records of ip_bans
-- ----------------------------

-- ----------------------------
-- Alter Sequences Owned By 
-- ----------------------------

-- ----------------------------
-- Primary Key structure for table "public"."account_social"
-- ----------------------------
ALTER TABLE "public"."account_social" ADD PRIMARY KEY ("guid");

-- ----------------------------
-- Primary Key structure for table "public"."accounts"
-- ----------------------------
ALTER TABLE "public"."accounts" ADD PRIMARY KEY ("guid");

-- ----------------------------
-- Primary Key structure for table "public"."game_servers"
-- ----------------------------
ALTER TABLE "public"."game_servers" ADD PRIMARY KEY ("id");
