<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $id = 0;
    $firstName = "";
    $lastName = "";

    $sql = "SELECT ID, FirstName, LastName FROM User where Login='" . $inData["login"] . "' and Password='" . $inData["password"] . "'";

    $result = $conn->query($sql);
    if ($result->num_rows > 0)
    {
        $row = $result->fetch_assoc();
        $firstName = $row["FirstName"];
        $lastName = $row["LastName"];
        $id = $row["ID"];

        returnWithInfo($firstName, $lastName, $id);
    }
    else
    {
        returnWithError("No Records Found");
    }
?>