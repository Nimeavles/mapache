<?php
    $names = array("Peter", "Pablo", "John");
?>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Apache Example</title>
</head>
<body>
    <h1>Apache example</h1>
    <hr>
    <?php foreach ($names as $name) { ?>
        <p><?php echo $name ?></p>
    <?php }?>
</body>
</html>