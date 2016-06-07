-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 05-06-2016 a las 20:00:00
-- Versión del servidor: 10.1.13-MariaDB
-- Versión de PHP: 5.6.20

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `cursodaw`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `address`
--

CREATE TABLE `address` (
  `id` int(11) NOT NULL,
  `user` int(10) UNSIGNED NOT NULL,
  `name` varchar(128) COLLATE utf8_spanish_ci NOT NULL,
  `street` varchar(256) COLLATE utf8_spanish_ci NOT NULL,
  `streetdoor` int(11) DEFAULT NULL,
  `housedoor` int(11) DEFAULT NULL,
  `city` varchar(64) COLLATE utf8_spanish_ci NOT NULL,
  `zip` varchar(8) COLLATE utf8_spanish_ci NOT NULL,
  `country` char(3) COLLATE utf8_spanish_ci NOT NULL,
  `deleted` tinyint(1) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `address`
--

INSERT INTO `address` (`id`, `user`, `name`, `street`, `streetdoor`, `housedoor`, `city`, `zip`, `country`, `deleted`) VALUES
(1, 1, 'Jorge Pérez', 'Avenida Valladolid', 14, 22, 'Valencia', '46020', 'ESP', 0),
(2, 1, 'Marcos', 'Av Valladolid', 13, NULL, 'Valencia', '46020', 'ESP', 1),
(3, 1, 'Marcos', 'Av Valladolid', 13, NULL, 'Valencia', '46020', 'ESP', 1),
(4, 1, 'Test Name', 'C/ Rue Percebe', 13, 2, 'Barcelona', '8080', 'ESP', 0),
(5, 2, 'Maria Abradelo', 'C/ Arquitecte Arnau', NULL, NULL, 'Valencia', '46020', 'ESP', 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cart`
--

CREATE TABLE `cart` (
  `user` int(11) UNSIGNED NOT NULL,
  `product` varchar(16) COLLATE utf8_spanish_ci NOT NULL,
  `quantity` int(11) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `countries`
--

CREATE TABLE `countries` (
  `code` char(3) COLLATE utf8_spanish_ci NOT NULL,
  `name` varchar(64) COLLATE utf8_spanish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `countries`
--

INSERT INTO `countries` (`code`, `name`) VALUES
('ABW', 'Aruba'),
('AFG', 'Afganistán'),
('AGO', 'Angola'),
('AIA', 'Anguila'),
('ALA', 'Islas Áland'),
('ALB', 'Albania'),
('AND', 'Andorra'),
('ANT', 'Antillas Neerlandesas'),
('ARE', 'Emiratos Árabes Unidos'),
('ARG', 'Argentina'),
('ARM', 'Armenia'),
('ASM', 'Samoa Americana'),
('ATA', 'Antártida'),
('ATF', 'Territorios Australes Franceses'),
('ATG', 'Antigua y Barbuda'),
('AUS', 'Australia'),
('AUT', 'Austria'),
('AZE', 'Azerbaiyán'),
('BDI', 'Burundi'),
('BEL', 'Bélgica'),
('BEN', 'Benin'),
('BFA', 'Burkina Faso'),
('BGD', 'Bangladesh'),
('BGR', 'Bulgaria'),
('BHR', 'Bahréin'),
('BHS', 'Bahamas'),
('BIH', 'Bosnia y Herzegovina'),
('BLM', 'San Bartolomé'),
('BLR', 'Belarús'),
('BLZ', 'Belice'),
('BMU', 'Bermudas'),
('BOL', 'Bolivia'),
('BRA', 'Brasil'),
('BRB', 'Barbados'),
('BRN', 'Brunéi'),
('BTN', 'Bhután'),
('BVT', 'Isla Bouvet'),
('BWA', 'Botsuana'),
('CAF', 'República Centro-Africana'),
('CAN', 'Canadá'),
('CCK', 'Islas Cocos'),
('CHE', 'Suiza'),
('CHL', 'Chile'),
('CHN', 'China'),
('CIV', 'Costa de Marfil'),
('CMR', 'Camerún'),
('COG', 'Congo'),
('COK', 'Islas Cook'),
('COL', 'Colombia'),
('COM', 'Comoros'),
('CPV', 'Cabo Verde'),
('CRI', 'Costa Rica'),
('CUB', 'Cuba'),
('CXR', 'Islas Christmas'),
('CYM', 'Islas Caimán'),
('CYP', 'Chipre'),
('CZE', 'República Checa'),
('DEU', 'Alemania'),
('DJI', 'Yibuti'),
('DMA', 'Domínica'),
('DNK', 'Dinamarca'),
('DOM', 'República Dominicana'),
('DZA', 'Argel'),
('ECU', 'Ecuador'),
('EGY', 'Egipto'),
('ERI', 'Eritrea'),
('ESH', 'Sahara Occidental'),
('ESP', 'España'),
('EST', 'Estonia'),
('ETH', 'Etiopía'),
('FIN', 'Finlandia'),
('FJI', 'Fiji'),
('FRA', 'Francia'),
('FRO', 'Islas Faroe'),
('FSM', 'Micronesia'),
('GAB', 'Gabón'),
('GBR', 'Reino Unido'),
('GEO', 'Georgia'),
('GGY', 'Guernsey'),
('GHA', 'Ghana'),
('GIB', 'Gibraltar'),
('GIN', 'Guinea'),
('GLP', 'Guadalupe'),
('GMB', 'Gambia'),
('GNB', 'Guinea-Bissau'),
('GNQ', 'Guinea Ecuatorial'),
('GRC', 'Grecia'),
('GRD', 'Granada'),
('GRL', 'Groenlandia'),
('GTM', 'Guatemala'),
('GUF', 'Guayana Francesa'),
('GUM', 'Guam'),
('GUY', 'Guayana'),
('HKG', 'Hong Kong'),
('HMD', 'Islas Heard y McDonald'),
('HND', 'Honduras'),
('HRV', 'Croacia'),
('HTI', 'Haití'),
('HUN', 'Hungría'),
('IDN', 'Indonesia'),
('IMN', 'Isla de Man'),
('IND', 'India'),
('IOT', 'Territorio Británico del Océano Índico'),
('IRL', 'Irlanda'),
('IRN', 'Irán'),
('IRQ', 'Irak'),
('ISL', 'Islandia'),
('ISR', 'Israel'),
('ITA', 'Italia'),
('JAM', 'Jamaica'),
('JEY', 'Jersey'),
('JOR', 'Jordania'),
('JPN', 'Japón'),
('KAZ', 'Kazajstán'),
('KEN', 'Kenia'),
('KGZ', 'Kirguistán'),
('KHM', 'Camboya'),
('KIR', 'Kiribati'),
('KLK', 'Islas Malvinas'),
('KNA', 'San Cristóbal y Nieves'),
('KOR', 'Corea del Sur'),
('KWT', 'Kuwait'),
('LAO', 'Laos'),
('LBN', 'Líbano'),
('LBR', 'Liberia'),
('LBY', 'Libia'),
('LCA', 'Santa Lucía'),
('LIE', 'Liechtenstein'),
('LKA', 'Sri Lanka'),
('LSO', 'Lesotho'),
('LTU', 'Lituania'),
('LUX', 'Luxemburgo'),
('LVA', 'Letonia'),
('MAC', 'Macao'),
('MAR', 'Marruecos'),
('MCO', 'Mónaco'),
('MDA', 'Moldova'),
('MDG', 'Madagascar'),
('MDV', 'Maldivas'),
('MEX', 'México'),
('MHL', 'Islas Marshall'),
('MKD', 'Macedonia'),
('MLI', 'Mali'),
('MLT', 'Malta'),
('MMR', 'Myanmar'),
('MNE', 'Montenegro'),
('MNG', 'Mongolia'),
('MOZ', 'Mozambique'),
('MRT', 'Mauritania'),
('MSR', 'Montserrat'),
('MTQ', 'Martinica'),
('MUS', 'Mauricio'),
('MWI', 'Malawi'),
('MYS', 'Malasia'),
('MYT', 'Mayotte'),
('NAM', 'Namibia'),
('NCL', 'Nueva Caledonia'),
('NER', 'Níger'),
('NFK', 'Islas Norkfolk'),
('NGA', 'Nigeria'),
('NIC', 'Nicaragua'),
('NIU', 'Niue'),
('NLD', 'Países Bajos'),
('NOR', 'Noruega'),
('NPL', 'Nepal'),
('NRU', 'Nauru'),
('NZL', 'Nueva Zelanda'),
('OMN', 'Omán'),
('PAK', 'Pakistán'),
('PAN', 'Panamá'),
('PCN', 'Islas Pitcairn'),
('PER', 'Perú'),
('PHL', 'Filipinas'),
('PLW', 'Islas Palaos'),
('PNG', 'Papúa Nueva Guinea'),
('POL', 'Polonia'),
('PRI', 'Puerto Rico'),
('PRK', 'Corea del Norte'),
('PRT', 'Portugal'),
('PRY', 'Paraguay'),
('PSE', 'Palestina'),
('PYF', 'Polinesia Francesa'),
('QAT', 'Qatar'),
('REU', 'Reunión'),
('ROU', 'Rumanía'),
('RUS', 'Rusia'),
('RWA', 'Ruanda'),
('SAU', 'Arabia Saudita'),
('SDN', 'Sudán'),
('SEN', 'Senegal'),
('SGP', 'Singapur'),
('SGS', 'Georgia del Sur e Islas Sandwich del Sur'),
('SHN', 'Santa Elena'),
('SJM', 'Islas Svalbard y Jan Mayen'),
('SLB', 'Islas Solomón'),
('SLE', 'Sierra Leona'),
('SLV', 'El Salvador'),
('SMR', 'San Marino'),
('SOM', 'Somalia'),
('SPM', 'San Pedro y Miquelón'),
('SRB', 'Serbia y Montenegro'),
('STP', 'Santo Tomé y Príncipe'),
('SUR', 'Surinam'),
('SVK', 'Eslovaquia'),
('SVN', 'Eslovenia'),
('SWE', 'Suecia'),
('SWZ', 'Suazilandia'),
('SYC', 'Seychelles'),
('SYR', 'Siria'),
('TCA', 'Islas Turcas y Caicos'),
('TCD', 'Chad'),
('TGO', 'Togo'),
('THA', 'Tailandia'),
('TJK', 'Tayikistán'),
('TKL', 'Tokelau'),
('TKM', 'Turkmenistán'),
('TLS', 'Timor-Leste'),
('TON', 'Tonga'),
('TTO', 'Trinidad y Tobago'),
('TUN', 'Túnez'),
('TUR', 'Turquía'),
('TUV', 'Tuvalu'),
('TWN', 'Taiwán'),
('TZA', 'Tanzania'),
('UGA', 'Uganda'),
('UKR', 'Ucrania'),
('URY', 'Uruguay'),
('USA', 'Estados Unidos de América'),
('UZB', 'Uzbekistán'),
('VAT', 'Ciudad del Vaticano'),
('VCT', 'San Vicente y las Granadinas'),
('VEN', 'Venezuela'),
('VGB', 'Islas Vírgenes Británicas'),
('VIR', 'Islas Vírgenes de los Estados Unidos de América'),
('VNM', 'Vietnam'),
('VUT', 'Vanuatu'),
('WLF', 'Wallis y Futuna'),
('WSM', 'Samoa'),
('YEM', 'Yemen'),
('ZAF', 'Sudáfrica');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `events`
--

CREATE TABLE `events` (
  `id` int(10) UNSIGNED NOT NULL,
  `description` varchar(128) COLLATE utf8_spanish_ci NOT NULL,
  `trackingurl` varchar(256) COLLATE utf8_spanish_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `events`
--

INSERT INTO `events` (`id`, `description`, `trackingurl`) VALUES
(1, 'Pedido creado', NULL),
(2, 'Pago recibido', NULL),
(3, 'Enviado por Correos', 'http://www.correos.es/ss/Satellite/site/aplicacion-1349167812834-herramientas_y_apps/detalle_app-sidioma=es_ES?numero=%tracking%'),
(4, 'Enviado por DHL', 'http://www.dhl.es/services_es/seg_3dd/integra/SeguimientoDocumentos.aspx?codigo=%tracking%&anno=2014&lang=sp'),
(5, 'Pedido cancelado', NULL),
(6, 'Esperando devolución', NULL);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `orderevents`
--

CREATE TABLE `orderevents` (
  `id` int(10) UNSIGNED NOT NULL,
  `orderid` int(10) UNSIGNED NOT NULL,
  `eventid` int(10) UNSIGNED NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `trackingcode` varchar(32) COLLATE utf8_spanish_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `orderevents`
--

INSERT INTO `orderevents` (`id`, `orderid`, `eventid`, `time`, `trackingcode`) VALUES
(1, 8, 1, '2016-06-03 11:45:50', NULL),
(2, 8, 3, '2016-06-03 11:47:57', 'RT075858171HK'),
(3, 9, 1, '2016-06-03 12:04:15', NULL),
(4, 8, 2, '2016-06-04 11:15:01', ''),
(5, 8, 6, '2016-06-04 11:15:25', ''),
(6, 8, 5, '2016-06-04 11:15:29', ''),
(7, 9, 2, '2016-06-04 14:34:39', ''),
(8, 10, 1, '2016-06-04 14:37:43', NULL),
(9, 10, 4, '2016-06-04 14:38:04', '8838239893ES'),
(10, 11, 1, '2016-06-04 14:39:04', NULL);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `orderproducts`
--

CREATE TABLE `orderproducts` (
  `orderid` int(10) UNSIGNED NOT NULL,
  `product` varchar(16) COLLATE utf8_spanish_ci NOT NULL,
  `quantity` int(10) UNSIGNED NOT NULL,
  `price` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `orderproducts`
--

INSERT INTO `orderproducts` (`orderid`, `product`, `quantity`, `price`) VALUES
(4, 'hexa', 1, '25.99'),
(5, 'hexa', 1, '25.99'),
(5, 'icaro', 3, '19.95'),
(6, 'hexa', 1, '25.99'),
(6, 'icaro', 3, '19.95'),
(7, 'hexa', 3, '25.99'),
(7, 'icaro', 7, '19.95'),
(8, 'hexa', 3, '25.99'),
(9, 'hexa', 3, '25.99'),
(10, 'hexa', 1, '25.99'),
(11, 'icaro', 1, '21.95');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `orders`
--

CREATE TABLE `orders` (
  `id` int(10) UNSIGNED NOT NULL,
  `address` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `orders`
--

INSERT INTO `orders` (`id`, `address`) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 1),
(8, 4),
(9, 4),
(10, 5),
(11, 5);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `products`
--

CREATE TABLE `products` (
  `id` varchar(16) COLLATE utf8_spanish_ci NOT NULL,
  `name` varchar(64) COLLATE utf8_spanish_ci NOT NULL,
  `description` text COLLATE utf8_spanish_ci NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `image` varchar(256) COLLATE utf8_spanish_ci DEFAULT NULL,
  `available` tinyint(1) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `products`
--

INSERT INTO `products` (`id`, `name`, `description`, `price`, `image`, `available`) VALUES
('hexa', 'Cama Hexa', '<p>Desencanto un dolorcillo apariencia ay. Cuyo se sera la este. Victorioso degenerado ha el zapatillas taciturnos confidente ch ha animandose. Estudiante suficiente haciendola imprevisto la gr yo el. Le de confidente sacrosanta embocadura aventurado no si. Si compositor encontrase tropezando mi se frecuentes escopetazo. Mal gozar brisa mayor ser por heroe curva. Prescindir estridente mia condenasen mas misteriosa montaraces pagarselos. Espontanea coqueteria adulterino alumbraban menudeaban gr yo lo logaritmos. Gorgheggi brigadier se homenajes necesario ma importuno maniobras.</p>\r\n\r\n<p>Traslucir ch encontrar recuerdos no temeraria. Quehaceres no casualidad al tranquilos ex arrepintio. Ano consuela epitetos ingresos italiano una don. Loco que ocho sino era rojo juro. Un lo he cola dios fija creo casa. Mismo nuevo iba nuevo luz son suyas echar.</p>\r\n\r\n<p>Habido sol volado luchar del pan quicio visita las. Cada debo ha dona sr sean pues. Tres cuya eran yo cuyo solo temo fe ya. Vendaval la heroismo cerraban molestar oh en. Tan eso salvacion mezclados exagerada chocolate que servicios del. Presencia ni eufemismo el artistico ch caballero separados. Va oh il renunciaba ahogandose bastidores habitacion. Doscientos la espectador cortesanos de animandose lamentable.</p>\r\n\r\n<p>Era las sociedades gas oyo respetable escopetazo. Amistad bajaban coronel excusar mi aparato siempre ni. Abofeteado ola anteriores pergaminos correccion consistido oyo rey vagabundos chi. Amparo sr consta dejase eterno carnes da dinero. Vio radiante allegros entendia gas convento extremos nos que. Reciente paradero mas simpatia inocente procrear contento ley por suo.</p>\r\n\r\n<p>Sus tan plebeyo chi persona lugares fue. Generosa cuidasen le mi entienda el id atencion mediodia aburrida. Podridos chillona ve declarar me gravedad publicas. He renovacion ve el suspirando superiores sonoliento. El os libreria asomaban sostengo victimas cornetin tu. Iba distantes fue esperanza fenomenos mia orgullosa chi comenzaba. Energico resultas oh eh lenguaje ilegales original epitetos. Hasta nueve fue verle tio darse sol don nubes debio.</p>\r\n\r\n<p>Atravesado logaritmos inquilinos movimiento sacamuelas fue ser ama non. Tio luego pobre tisis iba. Lo os provecho pintadas desairar pusieron. Saberlo ir hijuela en supiera renglon tisicos en. Non dar catadura quiebras entrados mal denomino. Soy admirando aguardaba presentar mal carinosos buscarlos clientela. Luz una tuvieron favorita pintados suo.</p>\r\n\r\n<p>Humor vivia doble ano fin clavo monte. Gloria sin rincon sea ola compas piedad aldeas por serena. Deliraba id encantos aterraba escribir juridico cominero el. Natural refirio iba empresa por oia. Tomaba palmas iba brusco delito efecto aca pueblo. Pegar ramas novia etc oyo desde carne.</p>\r\n\r\n<p>Iba quierame don audicion fin sufrirla prestaba sin tiospues. Enfermo lo costaba no hijuela un la comodas quedaba inmunda. Tu gallego encerro al robusto colonia un regular ah ocultar. Etc tio peligro era silbido pasmado. Poetizaba personaje siguiente sacerdote prestados ley desdenado mas los. Brisa pan joven gacha opera abrio mal armas.</p>\r\n\r\n<p>Sido le real de pano. Arrastraba escandalos devolverle ano pre mas ser. Si ha ma caer afan cada. Ve es embocadura romanticos dispersado discrecion el se aritmetico dispersion. Gas rey adoracion preterita por hermosura rodeabase palabrota. De primeros primeras tresillo favorita cantaron ex aparecer. Vivos ratos se ex estar ah si lejos. Almendras dos humillado sus aceptando exageraba. Ella suya lire acto da ya modo piso.</p>\r\n\r\n<p>Anteriores la orgullosos su misioneros tentandole estimarlos ventajosos va. De napolitana animandose no un creyendolo tu. Le hubiese ex caridad si tenores empresa negarle carrera. Solia palco luz grado llano uso hacia negra. Sucediera vacunaron consistia romantica mayuscula los tan palabrota. Levantaban fe enfermucha sonoliento dilettante continuaba su si. Eh si carrera senoras muertos ti lo piqueta. Sois piel anos ese dia ello pito cuyo.</p>', '25.99', '/static/products/hexa.jpg', 1),
('icaro', 'Cama Ícaro', '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam dictum eget eros at consectetur. Sed a ullamcorper quam. Sed at congue metus. Vestibulum sollicitudin risus eget tincidunt facilisis. Suspendisse cursus egestas convallis. Nulla vitae maximus eros, id laoreet metus. Pellentesque mollis augue metus, tempus sodales lacus consequat sit amet. Cras ultricies odio in turpis suscipit maximus. Pellentesque sapien metus, mattis quis euismod ut, bibendum et felis. Praesent et molestie orci. Quisque dictum vel ipsum nec dictum. Pellentesque vel imperdiet tellus. Ut enim neque, gravida ut vulputate maximus, aliquam in nulla. Donec viverra eleifend eros, sit amet placerat mi gravida a. Donec dolor arcu, mattis et dictum eget, ultricies vitae sem.</p>\r\n\r\n<p>Pellentesque eleifend vel est in finibus. Nullam placerat mi felis, eget sagittis libero mollis in. Interdum et malesuada fames ac ante ipsum primis in faucibus. Vestibulum quis euismod libero, ut aliquam nibh. Suspendisse congue vitae ante quis aliquet. Aliquam vitae iaculis massa. Ut feugiat condimentum eros ac lacinia. Donec eu purus mattis, dapibus felis quis, convallis elit. Etiam urna arcu, tempor et porta a, placerat nec quam. Curabitur tempor cursus arcu, at porttitor erat ultrices at. Pellentesque id luctus nisi, id posuere leo. Pellentesque interdum, purus vel dictum convallis, velit dolor maximus augue, ut interdum ipsum ligula et eros. Nam lorem risus, convallis nec sem vel, vestibulum facilisis erat.</p>\r\n\r\n<p>Ut et finibus nisl. In iaculis leo et est ultrices, quis vehicula nisi pharetra. Quisque finibus tincidunt neque, id accumsan lacus rutrum vel. Nullam sodales ut justo sed commodo. In auctor, sem vitae elementum pretium, ex lorem consectetur nisi, sit amet efficitur lectus odio vel velit. Mauris dapibus odio a tellus volutpat euismod. Curabitur consectetur sem vitae tortor bibendum tempor. In eleifend nisl a augue faucibus, quis mattis leo rhoncus.</p>\r\n\r\n<p>Vestibulum commodo consequat odio, sit amet commodo tellus porta sed. Praesent sit amet sapien vitae est vulputate convallis quis facilisis neque. Phasellus interdum semper orci sed feugiat. Nunc vehicula libero ullamcorper mauris varius fermentum. Donec felis arcu, molestie ac mollis quis, commodo in sem. Proin metus ipsum, faucibus sed ornare id, accumsan auctor risus. Quisque vehicula, purus a gravida scelerisque, ex tellus mollis odio, et pretium ligula est eget sapien. Quisque vel scelerisque enim, consectetur finibus urna. Vivamus ipsum ante, tempor eu luctus eu, mattis sed leo. Quisque venenatis eu ligula eu ultrices.</p>\r\n\r\n<p>Quisque egestas risus ut purus ultrices, vitae fermentum dolor vehicula. Integer id fringilla leo. Nam rutrum nulla vitae tellus ultricies, eu malesuada tortor molestie. Nam id urna fermentum, tristique orci sed, imperdiet eros. Phasellus maximus ornare varius. Pellentesque vehicula mollis nisl, vitae mollis nunc tincidunt vitae. Integer ut elit nec ex feugiat viverra non vel mauris. Proin ex eros, venenatis vel congue sit amet, bibendum ac lacus. Suspendisse fringilla lectus eu elit egestas pretium. Interdum et malesuada fames ac ante ipsum primis in faucibus.</p>', '21.95', '/static/products/icaro.jpg', 1),
('testprod', 'Producto de prueba 2!', '<p>Hola!</p>', '4.00', '', 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `email` varchar(64) COLLATE utf8_spanish_ci NOT NULL,
  `password` char(64) COLLATE utf8_spanish_ci NOT NULL,
  `level` tinyint(4) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

--
-- Volcado de datos para la tabla `users`
--

INSERT INTO `users` (`id`, `email`, `password`, `level`) VALUES
(1, 'socram8888@gmail.com', 'ee40f9f07c42164107954a1e45b70e7eefd295322c32a906e256089cc25ef9ae', 2),
(2, 'testuser@example.com', 'eb455b34ccca6f35671e708505008572a9df91f2a24337b0baceebc056993fa0', 1),
(3, 'blocked@example.com', 'd4cebb412778d32facbdec4d0253615fdfa0d77b293086f8e6c885111dd28bcf', 0);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `address`
--
ALTER TABLE `address`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `cart`
--
ALTER TABLE `cart`
  ADD PRIMARY KEY (`user`,`product`);

--
-- Indices de la tabla `countries`
--
ALTER TABLE `countries`
  ADD PRIMARY KEY (`code`);

--
-- Indices de la tabla `events`
--
ALTER TABLE `events`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `orderevents`
--
ALTER TABLE `orderevents`
  ADD PRIMARY KEY (`id`),
  ADD KEY `orderid` (`orderid`);

--
-- Indices de la tabla `orderproducts`
--
ALTER TABLE `orderproducts`
  ADD PRIMARY KEY (`orderid`,`product`);

--
-- Indices de la tabla `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `address`
--
ALTER TABLE `address`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT de la tabla `events`
--
ALTER TABLE `events`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT de la tabla `orderevents`
--
ALTER TABLE `orderevents`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT de la tabla `orders`
--
ALTER TABLE `orders`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
--
-- AUTO_INCREMENT de la tabla `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
