<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $contactID = $inData["contactID"];

    $userID = $inData["userID"];

    $error = "";

    foreach($inData as $key => $value) {
        if($value && strcmp($key, "contactID") != 0 && strcmp($key, "userID") != 0) {
            $success = mysqli_query($conn,"UPDATE Contacts SET ". $key ." = '". $value ."' WHERE (id = '". $contactID ."' AND UserID = '". $userID ."') LIMIT 1");
            $error .= ($success) ? "" : "Error: Failed to update " . $key . " for ContactID " . $contactID . "; ";
        }
    }

    $inData['error'] = $error;
    sendResultInfoAsJson(json_encode($inData));
?>
