-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Versión del servidor:         8.0.41 - MySQL Community Server - GPL
-- SO del servidor:              Win64
-- HeidiSQL Versión:             12.10.0.7000
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Volcando estructura de base de datos para sistema_vuelos
CREATE DATABASE IF NOT EXISTS `sistema_vuelos` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `sistema_vuelos`;

-- Volcando estructura para tabla sistema_vuelos.aeropuertos
CREATE TABLE IF NOT EXISTS `aeropuertos` (
  `id` int NOT NULL AUTO_INCREMENT,
  `codigo` varchar(10) NOT NULL,
  `nombre` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla sistema_vuelos.aeropuertos: ~3 rows (aproximadamente)
INSERT INTO `aeropuertos` (`id`, `codigo`, `nombre`) VALUES
	(3, 'FRS', 'MUNDO MAYA'),
	(4, 'GUA', 'LA AURORA'),
	(5, 'JFK', 'AEREOPUERTO INTERNACIONAL KENNEDY');

-- Volcando estructura para tabla sistema_vuelos.pasajeros
CREATE TABLE IF NOT EXISTS `pasajeros` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(100) NOT NULL,
  `apellido` varchar(100) NOT NULL,
  `email` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla sistema_vuelos.pasajeros: ~3 rows (aproximadamente)
INSERT INTO `pasajeros` (`id`, `nombre`, `apellido`, `email`) VALUES
	(1, 'JULIO', 'SEGURA', 'DAVIDSEG24@GMAIL.EDU.MX'),
	(2, 'CARLOS', 'LOPEZ', 'ECARL@MIUMG.EDU.GT'),
	(3, 'LUCAS', 'PODOSQUI', 'LUCAS123@GMAIL.COM');

-- Volcando estructura para tabla sistema_vuelos.reservas
CREATE TABLE IF NOT EXISTS `reservas` (
  `id` int NOT NULL AUTO_INCREMENT,
  `id_vuelo` int DEFAULT NULL,
  `id_pasajero` int DEFAULT NULL,
  `codigo_reserva` varchar(20) DEFAULT NULL,
  `numero_boleto` varchar(20) DEFAULT NULL,
  `asiento` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_vuelo` (`id_vuelo`),
  KEY `id_pasajero` (`id_pasajero`),
  CONSTRAINT `reservas_ibfk_1` FOREIGN KEY (`id_vuelo`) REFERENCES `vuelos` (`id`),
  CONSTRAINT `reservas_ibfk_2` FOREIGN KEY (`id_pasajero`) REFERENCES `pasajeros` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla sistema_vuelos.reservas: ~2 rows (aproximadamente)
INSERT INTO `reservas` (`id`, `id_vuelo`, `id_pasajero`, `codigo_reserva`, `numero_boleto`, `asiento`) VALUES
	(1, 1, 1, 'ER231', '123', '4A'),
	(2, 3, 2, 'ER342', '213', '3A');

-- Volcando estructura para tabla sistema_vuelos.usuarios_sistema
CREATE TABLE IF NOT EXISTS `usuarios_sistema` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre_usuario` varchar(50) NOT NULL,
  `contrasena` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla sistema_vuelos.usuarios_sistema: ~1 rows (aproximadamente)
INSERT INTO `usuarios_sistema` (`id`, `nombre_usuario`, `contrasena`) VALUES
	(1, 'DAVID', '1234');

-- Volcando estructura para tabla sistema_vuelos.vuelos
CREATE TABLE IF NOT EXISTS `vuelos` (
  `id` int NOT NULL AUTO_INCREMENT,
  `codigo_vuelo` varchar(10) NOT NULL,
  `id_origen` int DEFAULT NULL,
  `id_destino` int DEFAULT NULL,
  `fecha` date DEFAULT NULL,
  `hora_abordaje` time DEFAULT NULL,
  `hora_salida` time DEFAULT NULL,
  `hora_llegada` time DEFAULT NULL,
  `aerolinea` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `id_origen` (`id_origen`),
  KEY `id_destino` (`id_destino`),
  CONSTRAINT `vuelos_ibfk_1` FOREIGN KEY (`id_origen`) REFERENCES `aeropuertos` (`id`),
  CONSTRAINT `vuelos_ibfk_2` FOREIGN KEY (`id_destino`) REFERENCES `aeropuertos` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla sistema_vuelos.vuelos: ~3 rows (aproximadamente)
INSERT INTO `vuelos` (`id`, `codigo_vuelo`, `id_origen`, `id_destino`, `fecha`, `hora_abordaje`, `hora_salida`, `hora_llegada`, `aerolinea`) VALUES
	(1, '32GUPET34', 4, 3, '2025-07-02', '09:00:00', '09:15:00', '10:00:00', 'TAG'),
	(2, '3PETGUA2', 3, 4, '2025-07-04', '14:00:00', '14:15:00', '15:00:00', 'TAG'),
	(3, 'EU32GT', 5, 4, '2025-08-19', '10:00:00', '10:15:00', '20:15:00', 'AVIANCA');

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
