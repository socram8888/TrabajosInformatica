<?php
	define('BASE', '/daw');
	define('PASSWORDSALT', 'pdmWodWXkTrm4AfIAiu44a1yuOXvLGK432azyBYdAhlAL72quB8mvNzpqCxbkKpr');

	session_start();

	$mysqli = new mysqli("127.0.0.1", "root", "", "cursodaw");
	if ($mysqli->connect_error) {
		die('Error conectando a la base de datos: (' . $mysqli->connect_errno . ') ' . $mysqli->connect_error);
	}
	$mysqli->set_charset('utf8');

	function needs_level($level) {
		global $mysqli;

		if (isset($_SESSION['userid'])) {
			$res = $mysqli->query('SELECT 1 FROM users WHERE level >= 2 AND id = ' . $_SESSION['userid']);
			if (!$res) {
				die('Error comprobando privilegio del cliente');
			}

			if ($res->num_rows == 0) {
				unset($_SESSION['userid']);
			}
		}

		if ($level == 'admin' && !@$_SESSION['userid']) {
			header('302 Found', true, 302);
			header('Location: ' . BASE . '/login.php?redirect=' . urlencode(substr($_SERVER["REQUEST_URI"], strlen(BASE) + 1)));
			die();
		}
		
		if ($level == 'guest' && @$_SESSION['userid']) {
			header('302 Found', true, 302);
			header('Location: ' . BASE . '/');
			die();
		}
	}
?>