<?php
	require_once('template.inc.php');
	require_once('common.inc.php');
	
	needs_level('admin');

	$stmt = $mysqli->prepare("SELECT name, description, price, image, available FROM products WHERE id = ?");
	$stmt->bind_param('s', $_REQUEST['id']);
	$stmt->execute();
	
	$stmt->bind_result($name, $description, $price, $image, $available);
	if ($stmt->fetch()) {
		print_head('Editar ' . $_REQUEST['id']);
?>

		<form method="post" action="editproductexecute.php?id=<?php echo $_REQUEST['id']; ?>">
			<ul>
				<li><label for="name">Nombre</label>: <input type="text" maxlength="64" value="<?php echo $name; ?>" name="name" id="name"></li>
				<li>
					<label for="description">Descripción</label>:<br>
					<textarea name="description" id="description" style="width: 100%; height: 10em;"><?php echo htmlspecialchars($description); ?></textarea>
				</li>
				<li><label for="price">Precio</label>: <input type="number" value="<?php echo $price; ?>" name="price" id="price"></li>
				<li><label for="image">Imagen</label>: <input type="text" maxlength="256" value="<?php echo $image; ?>" name="image" id="image"></li>
				<li><label for="available">Disponible</label>: <input type="checkbox" name="available" id="available"<?php if ($available) { echo " checked"; } ?>></li>
			</ul>
			<input type="submit" value="Actualizar">
		</form>

		<p><a href="products.php">◄◄ Atrás</a></p>

<?php
	} else {
		print_head('Editar producto');
?>
		<p class="error">Producto no encontrado</p>
		<p><a href="products.php"><< Atrás</a></p>
<?php
	}

	$stmt->close();
	print_tail();
?>
