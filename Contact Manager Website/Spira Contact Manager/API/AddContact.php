<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $sql = "SELECT 1 FROM Contacts WHERE (UserID=? AND FirstName=? AND LastName=?) LIMIT 1";

    $stmt = $conn->prepare($sql);

    $stmt->bind_param("iss", $inData["userID"], $inData["firstName"], $inData["lastName"]);

    $stmt->bind_result($exists);

    if (!$stmt->execute()) {
        $inData['error'] = "Error in AddContact: Failed to query database";
        sendResultInfoAsJson(json_encode($inData));
        exit(1);
    }

    $stmt->fetch();

    $searchResults = "";
    if ($exists) {
        $inData['error'] = "Contact Exists";
        sendResultInfoAsJson(json_encode($inData));
    }
    else {
        $sql = "INSERT INTO Contacts (FirstName, LastName, Phone, Email, UserID) VALUES (?,?,?,?,?)";
        $stmt= $conn->prepare($sql);

        $stmt->bind_param("ssssi",
            $inData["firstName"],
            $inData["lastName"],
            $inData["phone"],
            $inData["email"],
            $inData["userID"]
        );

        if ($stmt->execute()) {
            $inData['error'] = "";
            sendResultInfoAsJson(json_encode($inData));
        } else {
            $inData['error'] = "Error in AddContact: Failed to update database";
            sendResultInfoAsJson(json_encode($inData));
        }
    }
?>
