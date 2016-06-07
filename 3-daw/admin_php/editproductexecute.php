<?php
	require_once('common.inc.php');
	needs_level('admin');

	$available = @$_REQUEST['available'] ? 1 : 0;

	$stmt = $mysqli->prepare("UPDATE products SET name = ?, description = ?, price = ?, image = ?, available = ? WHERE id = ?");
	$stmt->bind_param('ssdsis', $_REQUEST['name'], $_REQUEST['description'], $_REQUEST['price'], $_REQUEST['image'], $available, $_REQUEST['id']);
	$stmt->execute();
	$stmt->close();

	header('302 Found', true, 302);
	header('Location: editproduct.php?id=' . urlencode($_REQUEST['id']));
?>
