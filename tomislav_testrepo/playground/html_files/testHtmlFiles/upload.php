<!-- <?php
$targetDirectory = "uploads/"; // Directory where uploaded files will be stored
$targetFile = $targetDirectory . basename($_FILES["fileToUpload"]["name"]); // Get the file name

// Check if the file is uploaded successfully
if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $targetFile)) {
    echo "The file " . basename($_FILES["fileToUpload"]["name"]) . " has been uploaded.";
} else {
    echo "Sorry, there was an error uploading your file.";
}
?> -->

<?php
$response = array("success" => false, "error" => "Image upload failed");

if (isset($_FILES["image"])) {
    $targetDir = "uploads/";
    $targetFile = $targetDir . basename($_FILES["image"]["name"]);

    if (move_uploaded_file($_FILES["image"]["tmp_name"], $targetFile)) {
        $response["success"] = true;
        $response["image"] = $targetFile;
    }
}

header('Content-Type: application/json');
echo json_encode($response);
?>
