<?php
	require_once('template.inc.php');
	require_once('common.inc.php');
	
	needs_level('guest');

	print_head('Inicio de sesión');
?>

<?php if (isset($_REQUEST['failed'])) { ?>
	<p class="error">Error iniciando sesión. El correo y contraseña no se corresponde con el de ninguna cuenta de administración activa.</p>
<?php } ?>

<form method="post" action="loginexecute.php">
	<label for="email">Correo electrónico</label>: <input type="email" maxlength="64" name="email" id="email"><br>
	<label for="password">Contraseña</label>: <input type="password" name="password" id="password"><br>
	<input type="submit" value="Iniciar sesión">
</form>

<?php
	print_tail();
?>
