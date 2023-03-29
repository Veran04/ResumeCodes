<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $sql = "SELECT 1 FROM User WHERE Login='". $inData["login"] ."' LIMIT 1";

    $stmt = $conn->prepare($sql);
    $stmt->bind_result($exists);

    if (!$stmt->execute()) {
        $inData['error'] = "Error in Signup: Failed to query database";
        sendResultInfoAsJson(json_encode($inData));
        exit(1);
    }

    $stmt->fetch();

    $searchResults = "";
    if ($exists) {
        $inData['error'] = "Invalid Username";
        sendResultInfoAsJson(json_encode($inData));
    }
    else {
        $id = 0;

        $sql = "INSERT INTO User (Login, Password, FirstName, LastName) VALUES (?,?,?,?)";
        $stmt= $conn->prepare($sql);

        $stmt->bind_param("ssss",
            $inData["login"],
            $inData["password"],
            $inData["firstName"],
            $inData["lastName"]);

        $stmt->execute();

        $sql = "SELECT ID FROM User where Login='" . $inData["login"] . "' and Password='" . $inData["password"] . "'";

        $result = $conn->query($sql);
        if ($result->num_rows > 0)
        {
            $row = $result->fetch_assoc();
            $id = $row["ID"];

            returnWithInfo($inData["firstName"], $inData["lastName"], $id);
        }
        else
        {
            returnWithError("Error fetching from database");
        }
    }
?>
