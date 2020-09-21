-- MySQL dump 10.13  Distrib 8.0.21, for Linux (x86_64)
--
-- Host: localhost    Database: esb_db
-- ------------------------------------------------------
-- Server version	8.0.21-0ubuntu0.20.04.4

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `esb_request`
--

DROP TABLE IF EXISTS `esb_request`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `esb_request` (
  `id` int NOT NULL AUTO_INCREMENT,
  `sender_id` varchar(45) NOT NULL,
  `dest_id` varchar(45) NOT NULL,
  `message_type` varchar(45) NOT NULL,
  `reference_id` varchar(45) NOT NULL DEFAULT '2',
  `message_id` varchar(45) NOT NULL,
  `received_on` varchar(45) NOT NULL DEFAULT '2',
  `data_location` varchar(45) DEFAULT NULL,
  `status` varchar(45) NOT NULL,
  `status_details` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `esb_request`
--

LOCK TABLES `esb_request` WRITE;
/*!40000 ALTER TABLE `esb_request` DISABLE KEYS */;
INSERT INTO `esb_request` VALUES (1,'\'9874ca58-5e27-4275-a012-84ccdbae310d\'','\'b17cc80c-7d21-4c7b-86ad-25e6018a8578\'','\'sample\'','1','1','CURRENT_TIMESTAMP','1','processing','1'),(2,'x','y',' xml','2','2','2','2','1','1'),(3,'a','z','sample','3','3','3','3','3','3'),(11,'','','','','','2','','',''),(12,'','','','','','2','','',''),(13,'','','','','','2','','',''),(14,'','','','','','2','','',''),(15,'','','','','','2','','',''),(16,'','','','','','2','','',''),(17,'s1','d1','myxml','6','3','0002-01-00 00:00:00','random_loc','available','pc'),(18,'s1','d1','myxml','6','3','0002-01-00 00:00:00','random_loc','available','pc'),(19,'s1','d1','myxml','6','3','2020-09-05 17:49:13','random_loc','available','pc'),(20,'s2','d2','myxml','6','3','2020-09-05 18:10:46','random_loc','available','pc'),(21,'s3','d3','myxmlfile','7','7','2020-09-05 18:16:55','place','available','pc'),(22,'756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA','6393F82F-4687-433D-AA23-1966330381FE','CreditReport','INV-PROFILE-889712','A9ECAEF2-107A-4452-9553-043B6D25386E','2020-09-08 20:21:19','x','1','1'),(23,'756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA','6393F82F-4687-433D-AA23-1966330381FE','CreditReport','INV-PROFILE-889712','','2020-09-08 20:22:20','x','1','1'),(24,'a','z','sample','3','3','2020-09-10 12:51:43','/home/harshal/Desktop/bmd2.xml','file_received','1'),(25,'a','z','sample','3','3','2020-09-12 23:22:41','/home/harshal/Desktop/bmd2.xml','file_received','1'),(26,'a','z','sample','3','3','2020-09-12 23:42:02','/home/harshal/Desktop/bmd2.xml','file_received','1'),(28,'abc','xyz','IFSC','12','12','2020-09-15 18:33:07','/home/harshal/Desktop/bmd3.xml','done','1'),(29,'a','z','sample','3','3','2020-09-15 22:47:57','/home/harshal/Desktop/bmd2.xml','received','1'),(30,'a','z','sample','3','3','2020-09-16 10:59:23','/home/harshal/Desktop/bmd2.xml','received','1'),(31,'a','z','sample','3','3','2020-09-16 11:06:03','/home/harshal/Desktop/bmd2.xml','file_received','1'),(32,'a','z','sample','3','3','2020-09-16 11:12:09','/home/harshal/Desktop/bmd2.xml','file_received','1'),(33,'a','z','sample','3','3','2020-09-17 17:54:54','/home/harshal/Desktop/bmd2.xml','received','1'),(34,'a','z','sample','3','3','2020-09-18 12:47:23','/home/harshal/Desktop/bmd2.xml','received','1');
/*!40000 ALTER TABLE `esb_request` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `routes`
--

DROP TABLE IF EXISTS `routes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `routes` (
  `route_id` int NOT NULL,
  `sender` varchar(45) NOT NULL,
  `destination` varchar(45) NOT NULL,
  `message_type` varchar(45) NOT NULL,
  `is_active` bit(1) DEFAULT NULL,
  PRIMARY KEY (`route_id`,`sender`,`destination`),
  KEY `UK_sender_dest_msg_type` (`sender`,`message_type`,`destination`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `routes`
--

LOCK TABLES `routes` WRITE;
/*!40000 ALTER TABLE `routes` DISABLE KEYS */;
INSERT INTO `routes` VALUES (1,'a','z','sample',_binary ''),(2,'b','y','sample',_binary ''),(10,'abc','xyz','IFSC',_binary '');
/*!40000 ALTER TABLE `routes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transform_config`
--

DROP TABLE IF EXISTS `transform_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transform_config` (
  `id` int NOT NULL AUTO_INCREMENT,
  `route_id` int NOT NULL,
  `config_key` varchar(45) NOT NULL,
  `config_value` tinytext,
  PRIMARY KEY (`id`),
  KEY `route_idx` (`id`),
  KEY `UK_route_config` (`config_key`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transform_config`
--

LOCK TABLES `transform_config` WRITE;
/*!40000 ALTER TABLE `transform_config` DISABLE KEYS */;
INSERT INTO `transform_config` VALUES (1,1,'2','2'),(2,2,'3','3'),(3,10,'http','response');
/*!40000 ALTER TABLE `transform_config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transport_config`
--

DROP TABLE IF EXISTS `transport_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transport_config` (
  `id` int NOT NULL,
  `route_id` int NOT NULL,
  `config_key` varchar(45) DEFAULT NULL,
  `config_value` tinytext,
  PRIMARY KEY (`id`),
  KEY `route_idx` (`route_id`),
  KEY `UK_route_config` (`config_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transport_config`
--

LOCK TABLES `transport_config` WRITE;
/*!40000 ALTER TABLE `transport_config` DISABLE KEYS */;
INSERT INTO `transport_config` VALUES (1,1,'2','2'),(2,2,'3','3'),(3,10,'https://reqres.in/','api/users');
/*!40000 ALTER TABLE `transport_config` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-09-18 20:29:12
