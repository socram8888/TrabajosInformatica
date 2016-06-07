<?php
	require_once('template.inc.php');
	require_once('common.inc.php');

	needs_level('admin');

	print_head('Administración');
?>

<ul>
	<li><a href="products.php">Productos</a></li>
	<li><a href="users.php">Usuarios</a></li>
	<li><a href="orders.php">Pedidos</a></li>
	<li><a href="logout.php">Cerrar sesión</a></li>
</ul>

<?php print_tail(); ?>