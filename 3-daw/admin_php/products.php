<?php
	require_once('template.inc.php');
	require_once('common.inc.php');
	
	needs_level('admin');
	print_head('Productos');

	$query = $mysqli->query("SELECT id, name, price, available FROM products ORDER BY available DESC, id");
?>

<table>
	<tr>
		<th>Disp.</th>
		<th>Código</th>
		<th>Nombre</th>
		<th>Precio</th>
		<th>Editar</th>
	</tr>
	<?php while ($row = $query->fetch_row()) { ?>
		<tr>
			<td><?php if ($row[3]) echo "&#x2713;"; else echo "&#x2717;"; ?></td>
			<td><?php echo $row[0]; ?></td>
			<td><?php echo $row[1]; ?></td>
			<td><?php echo $row[2]; ?> €</td>
			<td><a href="editproduct.php?id=<?php echo $row[0]; ?>">►►</a></td>
		</tr>
	<?php } ?>
	<tr>
		<td colspan="5"><a href="newproduct.php">Crear nuevo</a></td>
	</tr>
</table>

<p><a href="index.php">◄◄ Atrás</a></p>

<?php
	$query->close();
	print_tail();
?>
