<?php
	require_once('common.inc.php');
	needs_level('admin');

	$available = @$_REQUEST['available'] ? 1 : 0;

	$stmt = $mysqli->prepare("INSERT INTO products(id, name, description, price, image, available) VALUES (?, ?, ?, ?, ?, ?)");
	$stmt->bind_param('sssdsi', $_REQUEST['id'], $_REQUEST['name'], $_REQUEST['description'], $_REQUEST['price'], $_REQUEST['image'], $available);
	$stmt->close();

	header('302 Found', true, 302);
	header('Location: editproduct.php?id=' . urlencode($_REQUEST['id']));
?>
