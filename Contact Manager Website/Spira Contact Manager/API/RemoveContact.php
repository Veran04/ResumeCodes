<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $sql = "DELETE FROM Contacts where (id=? AND UserID=?)";
    $stmt= $conn->prepare($sql);

    $stmt->bind_param("ii", $inData["contactID"], $inData["userID"]);

    if ($stmt->execute()) {
        $inData['error'] = "";
        sendResultInfoAsJson(json_encode($inData));
    } else {
        $inData['error'] = "Error in RemoveContact: Failed to update database";
        sendResultInfoAsJson(json_encode($inData));
    }
?>
