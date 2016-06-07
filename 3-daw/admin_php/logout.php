<?php

session_start();
unset($_SESSION['userid']);

header('302 Found', true, 302);
header('Location: login.php');

?>