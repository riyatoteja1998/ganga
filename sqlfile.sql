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
  `id` int NOT NULL,
  `sender_id` varchar(45) NOT NULL,
  `dest_id` varchar(45) NOT NULL,
  `message_type` varchar(45) NOT NULL,
  `reference_id` varchar(45) NOT NULL,
  `message_id` varchar(45) NOT NULL,
  `received_on` varchar(45) NOT NULL,
  `data_location` varchar(45) DEFAULT NULL,
  `status` varchar(45) NOT NULL,
  `status_details` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `esb_request`
--

LOCK TABLES `esb_request` WRITE;
/*!40000 ALTER TABLE `esb_request` DISABLE KEYS */;
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
/*!40000 ALTER TABLE `routes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transform_config`
--

DROP TABLE IF EXISTS `transform_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transform_config` (
  `id` int NOT NULL,
  `route_id` int NOT NULL,
  `config_key` varchar(45) NOT NULL,
  `config_value` tinytext,
  PRIMARY KEY (`id`),
  KEY `route_idx` (`id`),
  KEY `UK_route_config` (`config_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transform_config`
--

LOCK TABLES `transform_config` WRITE;
/*!40000 ALTER TABLE `transform_config` DISABLE KEYS */;
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
  `route_id` varchar(45) DEFAULT NULL,
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

-- Dump completed on 2020-08-28  0:17:23
