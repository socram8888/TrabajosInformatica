<?php
	require_once('common.inc.php');
	needs_level('admin');

	$available = @$_REQUEST['available'] ? 1 : 0;

	$stmt = $mysqli->prepare("UPDATE users SET email = ?, level = ? WHERE id = ?");
	$stmt->bind_param('sii', $_REQUEST['email'], $_REQUEST['level'], $_REQUEST['id']);
	$stmt->execute();
	$stmt->close();

	header('302 Found', true, 302);
	header('Location: users.php');
?>
