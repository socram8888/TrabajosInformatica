<?php

require_once('template.inc.php');
require_once('common.inc.php');

needs_level('admin');
print_head('Crear producto');

?>
<form method="post" action="newproductexecute.php">
	<ul>
		<li><label for="id">Código único</label>: <input type="text" maxlength="16" name="id" id="id"></li>
		<li><label for="name">Nombre</label>: <input type="text" maxlength="64" name="name" id="name"></li>
		<li>
			<label for="description">Descripción</label>:<br>
			<textarea name="description" id="description" style="width: 100%; height: 10em;"></textarea>
		</li>
		<li><label for="price">Precio</label>: <input type="number" name="price" id="price"></li>
		<li><label for="image">Imagen</label>: <input type="text" maxlength="256" name="image" id="image"></li>
		<li><label for="available">Disponible</label>: <input type="checkbox" name="available" id="available"></li>
	</ul>
	<input type="submit" value="Crear">
</form>

<p><a href="products.php">◄◄ Atrás</a></p>
<?php
	print_tail();
?>
