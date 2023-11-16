<?php
$mp3Files = [];

$files = scandir(__DIR__);
foreach ($files as $file) {
    if (pathinfo($file, PATHINFO_EXTENSION) === 'mp3') {
        $mp3Files[] = [
            'name' => $file,
            'path' => $file,
        ];
    }
}

header('Content-Type: application/json');
echo json_encode($mp3Files);
?>

