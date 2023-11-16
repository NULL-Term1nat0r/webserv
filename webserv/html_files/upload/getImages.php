<?php

$dir = '.'; // Change this to the directory path you want to scan
$allowedExtensions = ['jpg', 'jpeg', 'png'];

$images = array_filter(scandir($dir), function($file) use ($allowedExtensions) {
    $extension = pathinfo($file, PATHINFO_EXTENSION);
    return in_array($extension, $allowedExtensions);
});

echo json_encode($images);

?>
