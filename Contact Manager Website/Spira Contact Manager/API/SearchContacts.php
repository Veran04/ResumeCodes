<?php
    require_once("config.php");

    $inData = getRequestInfo();

    $search = $inData["search"];

    $sql = "SELECT * FROM Contacts WHERE UserID='" . $inData["userID"] . "'";
    $sql .= " AND (FirstName LIKE '%" . $search . "%'";
    $sql .= " OR LastName LIKE '%" . $search . "%'";
    $sql .= " OR concat(FirstName, ' ', LastName) LIKE '%" . $search . "%'";
    $sql .= " OR concat(LastName, ' ', FirstName) LIKE '%" . $search . "%'";
    $sql .= " OR Phone LIKE '%" . $search . "%'";
    $sql .= " OR DateCreated LIKE '%" . $search . "%'";
    $sql .= " OR Email LIKE '%" . $search . "%')";
    $sql .= " ORDER BY FirstName, LastName, Email, Phone ASC";

    $result = $conn->query($sql);

    $searchResults = "";

    $searchResults = packageContactsAsJson($result);

    sendResultInfoAsJson( $searchResults );

?>
