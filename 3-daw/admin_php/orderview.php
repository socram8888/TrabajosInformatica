<?php
	require_once('template.inc.php');
	require_once('common.inc.php');

	needs_level('admin');

	$orderQuery = $mysqli->prepare("
		SELECT address.name AS name, street, streetdoor, housedoor, city, zip, countries.name AS country, users.id, email
				FROM orders
				JOIN address ON orders.address = address.id
				JOIN countries ON address.country = countries.code
				JOIN users ON address.user = users.id
				WHERE orders.id = ?;
	");
	$orderQuery->bind_param('i', $_REQUEST['id']);
	$orderQuery->execute();

	$orderQuery->bind_result($name, $street, $streetdoor, $housedoor, $city, $zip, $country, $userId, $email);
	$orderExists = $orderQuery->fetch();
	$orderQuery->close();
	if ($orderExists) {
		print_head('Orden #' . $_REQUEST['id']);
?>
		<ul>
			<li>Usuario: <?php echo $email; ?></li>
			<li>Destino:
				<?php
					echo "$name, $street, ";
					if ($streetdoor) echo "Nº $streetdoor, ";
					if ($housedoor) echo "Pta $housedoor, ";
					echo "$city, CP $zip, $country";
				?>
			</li>
		</ul>
		
		<h2>Estado</h2>
		<table>
			<tr>
				<th>Fecha</th>
				<th>Estado</th>
				<th>Seguimiento</th>
			</tr>

<?php
	$statusQuery = $mysqli->prepare("
		SELECT time, description, trackingurl, trackingcode
				FROM orderevents
				JOIN events ON orderevents.eventid = events.id
				WHERE orderid = ?
				ORDER BY time DESC;
	");
	$statusQuery->bind_param('i', $_REQUEST['id']);

	$statusQuery->execute();
	$statusQuery->bind_result($time, $description, $trackingUrl, $trackingCode);

	while ($statusQuery->fetch()) {
?>
			<tr>
				<td><?php echo $time; ?></td>
				<td><?php echo $description; ?></td>
				<td>
					<?php
						if ($trackingUrl && $trackingCode) {
							echo "<a href=\"" . str_replace('%tracking%', $trackingCode, $trackingUrl) . "\" target=\"_blank\">$trackingCode</a>";
						} else if ($trackingCode) {
							echo $trackingCode;
						}
					?>
				</td>
			</tr>
<?php
	}
	$statusQuery->close();
?>
		</table>

		<h3>Actualizar</h3>
		<table>
			<tr>
				<th>Estado</th>
				<th>Seguimiento</th>
				<th>Actualizar</th>
			</tr>

			<tr>
				<form method="post" action="orderstatusadd.php?id=<?php echo $_REQUEST['id']; ?>">
				<td>
						<select name="status">
<?php
	$eventsQuery = $mysqli->prepare("
		SELECT id, description FROM events ORDER BY description;
	");

	$eventsQuery->execute();
	$eventsQuery->bind_result($id, $description);

	while ($eventsQuery->fetch()) {
		echo "<option value=\"$id\">$description</option>";
	}
	$eventsQuery->close();
?>
						</select>
					</td>
					<td><input type="text" name="tracking" maxlength="32"></td>
					<td><input type="submit" value="►►"></td>
				</form>
			</tr>
		</table>

		<h2>Productos</h2>
		<table id="carttable">
			<tr>
				<th>Producto</th>
				<th>Subtotal</th>
				<th>Cantidad</th>
			</tr>

<?php
	$productQuery = $mysqli->prepare("
		SELECT name, quantity, orderproducts.price * quantity AS subtotal
				FROM orderproducts
				JOIN products ON orderproducts.product = products.id
				WHERE orderid = ?;
	");
	$productQuery->bind_param('i', $_REQUEST['id']);

	$productQuery->execute();
	$productQuery->bind_result($name, $quantity, $subtotal);
	$total = 0;

	while ($productQuery->fetch()) {
		$total += $subtotal;
?>

				<tr>
					<td><?php echo $name; ?></td>
					<td><?php echo $subtotal; ?> €</td>
					<td><?php echo $quantity; ?></td>
				</tr>
<?php
	}
	$productQuery->close();
?>
		</table>
		<p>Total: <?php echo $total; ?> €</p>

		<p><a href="orders.php">◄◄ Atrás</a></p>

<?php
	} else {
		print_head('Ver pedido');
?>
		<p class="error">Pedido no encontrado</p>
		<p><a href="orders.php">◄◄ Atrás</a></p>
<?php
	}

	print_tail();
?>
