<?php
	require_once('common.inc.php');
	needs_level('admin');

	$stmt = $mysqli->prepare("INSERT INTO orderevents(orderid, eventid, trackingcode) VALUES (?, ?, ?)");
	$stmt->bind_param('iis', $_REQUEST['id'], $_REQUEST['status'], $_REQUEST['tracking']);
	$stmt->execute();
	$stmt->close();

	header('302 Found', true, 302);
	header('Location: orderview.php?id=' . urlencode($_REQUEST['id']));
?>
