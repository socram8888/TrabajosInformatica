<?php
	require_once('common.inc.php');
	needs_level('guest');

	$stmt = $mysqli->prepare("SELECT id FROM users WHERE email = ? AND password = SHA2(CONCAT('" . PASSWORDSALT . "', 0x00, email, 0x00, ?), 256) AND level >= 2 LIMIT 1");
	$stmt->bind_param('ss', $_REQUEST['email'], $_REQUEST['password']);
	$stmt->execute();
	
	$stmt->bind_result($_SESSION['userid']);
	$stmt->fetch();
	$stmt->close();

	header('302 Found', true, 302);
	if (@$_SESSION['userid']) {
		header('Location: ' . BASE . '/' . @$_REQUEST['redirect']);
	} else {
		header('Location: login.php?failed=true');
	}
?>
