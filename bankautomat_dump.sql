CREATE DATABASE  IF NOT EXISTS `bankautomat` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bankautomat`;
-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bankautomat
-- ------------------------------------------------------
-- Server version	8.0.23

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
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `idAsiakas` int NOT NULL AUTO_INCREMENT,
  `nimi` varchar(45) NOT NULL,
  `osoite` varchar(45) NOT NULL,
  `puhelinnumero` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idAsiakas`),
  UNIQUE KEY `idAsiakas_UNIQUE` (`idAsiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Yksikorttimies_1','a','1'),(2,'Yksikorttimies_2','b','2'),(3,'Monikorttimies','c','3');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `asiakastili`
--

DROP TABLE IF EXISTS `asiakastili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakastili` (
  `idAsiakasTili` int NOT NULL AUTO_INCREMENT,
  `idAsiakas` int NOT NULL,
  `idTilinumero` varchar(45) NOT NULL,
  PRIMARY KEY (`idAsiakasTili`),
  UNIQUE KEY `idAsiakasTili_UNIQUE` (`idAsiakasTili`),
  KEY `idAsiakas_idx` (`idAsiakas`),
  KEY `idTilinumero_idx` (`idTilinumero`),
  CONSTRAINT `idAsiakas` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `idTilinumero1` FOREIGN KEY (`idTilinumero`) REFERENCES `tili` (`idTilinumero`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakastili`
--

LOCK TABLES `asiakastili` WRITE;
/*!40000 ALTER TABLE `asiakastili` DISABLE KEYS */;
INSERT INTO `asiakastili` VALUES (1,1,'Tili_1'),(2,2,'Tili_1'),(3,3,'Tili_2'),(4,3,'Tili_3');
/*!40000 ALTER TABLE `asiakastili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `idKortti` int NOT NULL AUTO_INCREMENT,
  `pin` varchar(255) NOT NULL,
  `idTilinumero` varchar(45) NOT NULL,
  `idAsiakas` int NOT NULL,
  PRIMARY KEY (`idKortti`),
  UNIQUE KEY `idKortti_UNIQUE` (`idKortti`),
  KEY `idTilinumero_idx` (`idTilinumero`),
  KEY `idAsiakas_idx` (`idAsiakas`),
  CONSTRAINT `idAsiakas1` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `idTilinumero0` FOREIGN KEY (`idTilinumero`) REFERENCES `tili` (`idTilinumero`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES (1,'0000','Tili_1',1),(2,'1111','Tili_1',2),(3,'2222','Tili_2',3),(4,'3333','Tili_3',3);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `idTilinumero` varchar(45) NOT NULL,
  `saldo` double NOT NULL DEFAULT '0',
  PRIMARY KEY (`idTilinumero`),
  UNIQUE KEY `idTilinumero_UNIQUE` (`idTilinumero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES ('Tili_1',1000),('Tili_2',1000),('Tili_3',1000);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtuma`
--

DROP TABLE IF EXISTS `tilitapahtuma`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtuma` (
  `idTilitapahtuma` int NOT NULL AUTO_INCREMENT,
  `idTilinumero` varchar(45) NOT NULL,
  `dateTime` datetime NOT NULL,
  `summa` double NOT NULL,
  `tilitapahtuma` varchar(45) NOT NULL,
  `idKortti` int NOT NULL,
  PRIMARY KEY (`idTilitapahtuma`),
  UNIQUE KEY `idTilitapahtuma_UNIQUE` (`idTilitapahtuma`),
  KEY `idTilinumero` (`idTilinumero`),
  CONSTRAINT `idTilinumero` FOREIGN KEY (`idTilinumero`) REFERENCES `tili` (`idTilinumero`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtuma`
--

LOCK TABLES `tilitapahtuma` WRITE;
/*!40000 ALTER TABLE `tilitapahtuma` DISABLE KEYS */;
/*!40000 ALTER TABLE `tilitapahtuma` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bankautomat'
--
/*!50003 DROP PROCEDURE IF EXISTS `nosto` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `nosto`(IN kortinnro INT, IN tilinro VARCHAR(45), IN rahasumma DOUBLE)
BEGIN
DECLARE test INT DEFAULT 0;
START TRANSACTION;
UPDATE tili SET saldo = saldo-rahasumma WHERE idTilinumero = tilinro;
SET test = ROW_COUNT();

IF(test > 0) THEN
COMMIT;
INSERT INTO tilitapahtuma(idTilinumero, idKortti, dateTime, summa, tilitapahtuma) VALUES(tilinro, kortinnro, NOW(), rahasumma, "Nosto");
ELSE
ROLLBACK;

END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `talletus` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `talletus`(IN kortinnro INT, IN tilinro VARCHAR(45), IN rahasumma DOUBLE)
BEGIN
DECLARE test INT DEFAULT 0;
START TRANSACTION;
UPDATE tili SET saldo = saldo+rahasumma WHERE idTilinumero = tilinro;
SET test = ROW_COUNT();

IF(test > 0) THEN
COMMIT;
INSERT INTO tilitapahtuma(idTilinumero, idKortti, dateTime, summa, tilitapahtuma) VALUES(tilinro, kortinnro, NOW(), rahasumma, "Talletus");
ELSE
ROLLBACK;

END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `tilisiirto` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `tilisiirto`(IN kortinnro INT, IN sendertilinro VARCHAR(45), IN receivertilinro VARCHAR(45), IN rahasumma DOUBLE)
BEGIN
DECLARE test1, test2 INT DEFAULT 0;
START TRANSACTION;
UPDATE tili SET saldo = saldo-rahasumma WHERE idTilinumero = sendertilinro;
SET test1 = ROW_COUNT();
UPDATE Tili SET saldo = saldo+rahasumma WHERE idTilinumero = receivertilinro;
SET test2 = ROW_COUNT();

IF(test1 > 0 AND test2 > 0) THEN
COMMIT;
INSERT INTO tilitapahtuma(idTilinumero, idKortti, dateTime, summa, tilitapahtuma) VALUES(sendertilinro, kortinnro, NOW(), rahasumma, "Lähtevä tilisiirto");
INSERT INTO tilitapahtuma(idTilinumero, idKortti, dateTime, summa, tilitapahtuma) VALUES(receivertilinro, kortinnro, NOW(), rahasumma, "Saapuva tilisiirto");
ELSE
ROLLBACK;

END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-01 10:59:04
