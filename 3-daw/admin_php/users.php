<?php
	require_once('template.inc.php');
	require_once('common.inc.php');
	
	needs_level('admin');
	print_head('Usuarios');

	$query = $mysqli->query("SELECT id, email, level FROM users ORDER BY id");
?>

<table>
	<tr>
		<th>ID</th>
		<th>Email</th>
		<th>Privilegios</th>
		<th>Actualizar</th>
	</tr>
	<?php while ($row = $query->fetch_row()) { ?>
		<tr>
			<form method="post" action="usersedit.php">
				<input type="hidden" name="id" value="<?php echo $row[0]; ?>">
				<td><?php echo $row[0]; ?></td>
				<td><input type="email" value="<?php echo $row[1]; ?>" name="email" maxlength="64"></td>
				<td>
					<select name="level">
						<option value="0"<?php if ($row[2] == 0) echo " selected"; ?>>Bloqueada</option>
						<option value="1"<?php if ($row[2] == 1) echo " selected"; ?>>Usuario</option>
						<option value="2"<?php if ($row[2] == 2) echo " selected"; ?>>Administrador</option>
					</select>
				<td><input type="submit" value="►►"></td>
			</form>
		</tr>
	<?php } ?>
</table>

<p><a href="index.php">◄◄ Atrás</a></p>

<?php
	$query->close();
	print_tail();
?>
