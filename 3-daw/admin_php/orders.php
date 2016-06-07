<?php
	require_once('template.inc.php');
	require_once('common.inc.php');

	needs_level('admin');
	print_head('Pedidos');

	$query = $mysqli->query("
		SELECT orders.id, description AS status, time
                FROM orders
                JOIN orderevents ON orders.id = orderevents.orderid
                JOIN events ON orderevents.eventid = events.id
                    AND orderevents.id = (
                        SELECT id FROM orderevents
                            WHERE orderid = orders.id ORDER BY time DESC LIMIT 1)
                ORDER BY time DESC;
	");
?>

<table>
	<tr>
		<th>ID</th>
		<th>Estado</th>
		<th>Fecha</th>
		<th>Actualizar</th>
	</tr>
	<?php while ($row = $query->fetch_row()) { ?>
		<tr>
			<td><?php echo $row[0]; ?></td>
			<td><?php echo $row[1]; ?></td>
			<td><?php echo $row[2]; ?></td>
			<td>
				<a href="orderview.php?id=<?php echo $row[0]; ?>">►►</a>
			</td>
		</tr>
	<?php } ?>
</table>

<p><a href="index.php">◄◄ Atrás</a></p>

<?php
	$query->close();
	print_tail();
?>
