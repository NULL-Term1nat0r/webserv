<!DOCTYPE html>
<html>
<head>
    <title>CGI Example</title>
</head>
<body>

<?php
parse_str($_SERVER['QUERY_STRING'], $params);
$name = $params['name'];

echo "<h1>Hello dude, ";
if ($name) {
    echo "$name!";
} else {
    echo "No name provided.";
}
echo "</h1>";
?>

</body>
</html>