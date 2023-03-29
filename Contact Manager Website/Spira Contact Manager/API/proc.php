<?php

  require_once("config.php");
  $msg  = "";
	$inData = getRequestInfo();
	$id = 0;
  $sql_u = "($conn,SELECT * FROM User WHERE ID=" . $inData["id"] . ")";
  $res_u = mysqli_num_rows($sql_u);
  
  if ($res_u > 0) 
  {
    $msg = "Username Already Taken.";
    else 
    {
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
  }    
?>
