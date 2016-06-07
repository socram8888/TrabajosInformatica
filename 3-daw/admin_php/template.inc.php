<?php function print_head($title) { ?>
<!DOCTYPE html>
<html>
    <head>
        <title><?php echo $title; ?> - SleepingDogs</title>
        <meta charset="utf-8">
        <link rel="stylesheet" type="text/css" href="static/style.css">
    </head>
    <body>
        <div id="logo">
            <h1>Sleeping<wbr>Dogs</h1>
        </div>
        <div id="content">
			<h1><?php echo $title; ?></h1>
<?php } ?>

<?php function print_tail() { ?>
        </div>
        <div id="footer">
            &copy;2016 <a href="https://socram.ovh/">socram</a>
        </div>
    </body>
</html>
<?php } ?>
