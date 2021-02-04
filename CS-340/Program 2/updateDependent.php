<?php
    session_start();
    ob_start();
// Include config file
	require_once "config.php";
 
// Define variables and initialize with empty values
// Note: You can not update SSN 
$Dname = $Relationship = $Bdate = $Bdate1 = $Sex = "";
$Ssn_err = $Dname_err = $Relationship_err = $Bdate_err = $Sex_err = "";
// Form default values

if(isset($_GET["Ssn"]) && !empty(trim($_GET["Ssn"])) && isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
    $_SESSION["Ssn"] = $_GET["Ssn"];
    $_SESSION["Dname"] = $_GET["Dname"];

    // Prepare a select statement
    $sql1 = "SELECT * FROM DEPENDENT WHERE Ssn = ? AND Dependent_name = ?";
  
    if($stmt1 = mysqli_prepare($link, $sql1)){
        // Bind variables to the prepared statement as parameters
        mysqli_stmt_bind_param($stmt1, "ss", $param_Ssn, $param_Dname);      
        // Set parameters
       $param_Ssn = trim($_GET["Ssn"]);
       $param_Dname = trim($_GET["Dname"]);

        // Attempt to execute the prepared statement
        if(mysqli_stmt_execute($stmt1)){
            $result1 = mysqli_stmt_get_result($stmt1);
			if(mysqli_num_rows($result1) > 0){

				$row = mysqli_fetch_array($result1);

				$Dname = $row['Dependent_name'];
				$Relationship = $row['Relationship'];
				$Bdate = $row['Bdate'];
				$Sex = $row['Sex'];
			}
		}
	}
}

 
// Post information about the employee when the form is submitted
// Processing form data when form is submitted
if($_SERVER["REQUEST_METHOD"] == "POST"){
    // the id is hidden and can not be changed
    $Ssn = $_SESSION["Ssn"];
    $OldD = $_SESSION["Dname"];
    // Validate form data this is similar to the create Employee file
    
    // Validate name
    $Dname = trim($_POST["Dname"]);
    if(empty($Dname)){
        $Dname_err = "Please enter a dependent name.";
    } elseif(!filter_var($Dname, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"/^[a-zA-Z\s]+$/")))){
        $Dname_err = "Please enter a valid dependent name.";
    } 

    // Validate Relationship
    $Relationship = trim($_POST["Relationship"]);
    if(empty($Relationship)){
        $Relationship_err = "Please enter Relationship.";     
    }
	
	// Validate Sex
    $Sex = trim($_POST["Sex"]);
    if(empty($Sex)){
        $Sex_err = "Please enter Sex.";    	
	}
	
	// Validate birth date
    $Bdate = trim($_POST["Bdate"]);
    if(empty($Bdate)){
        $Bdate_err = "Please enter birth date.";    	
	}

    // Check input errors before inserting into database
    if(empty($Dname_err) && empty($Relationship_err) && empty($Bdate_err) && empty($Sex_err)){
        // Prepare an update statement
        $sql = "UPDATE DEPENDENT SET Dependent_name=?, Relationship=?, Bdate=?, Sex = ? WHERE Essn=? AND Dependent_name=?";
    
        if($stmt = mysqli_prepare($link, $sql)){
            // Bind variables to the prepared statement as parameters
            mysqli_stmt_bind_param($stmt, "ssssss", $param_Dname, $param_Relationship, $param_Bdate, $param_Sex, $param_Ssn, $param_olD);
            
            // Set parameters
            $param_Dname = $Dname;
	    $param_Relationship = $Relationship;            
	    $param_Bdate = $Bdate;
            $param_Sex = $Sex;
            $param_Ssn = $Ssn;
            $param_olD = $OldD;
            
            // Attempt to execute the prepared statement
            if(mysqli_stmt_execute($stmt)){
                // Records updated successfully. Redirect to landing page
                header("location: index.php");
                exit();
            } else{
                echo "<center><h2>Error when updating</center></h2>";
            }
        }        
        // Close statement
        mysqli_stmt_close($stmt);
    }
    
    // Close connection
    mysqli_close($link);
} else {

    // Check existence of sID parameter before processing further
	// Form default values

	if(isset($_GET["Ssn"]) && !empty(trim($_GET["Ssn"])) && isset($_GET["Dname"]) && !empty(trim($_GET["Dname"]))){
                $_SESSION["Ssn"] = $_GET["Ssn"];
                $_SESSION["Dname"] = $_GET["Dname"];

		// Prepare a select statement
		$sql1 = "SELECT * FROM DEPENDENT WHERE Essn = ? AND Dependent_name = ?";
  
		if($stmt1 = mysqli_prepare($link, $sql1)){
			// Bind variables to the prepared statement as parameters
			mysqli_stmt_bind_param($stmt1, "ss", $param_Ssn, $param_Dname);      
			// Set parameters
                        $param_Ssn = trim($_GET["Ssn"]);
                        $param_Dname = trim($_GET["Dname"]);

			// Attempt to execute the prepared statement
			if(mysqli_stmt_execute($stmt1)){
				$result1 = mysqli_stmt_get_result($stmt1);
				if(mysqli_num_rows($result1) == 1){

					$row = mysqli_fetch_array($result1);

					$Dname = $row['Dependent_name'];
					$Relationship = $row['Relationship'];
					$Bdate = $row['Bdate'];
					$Sex = $row['Sex'];
				} else{
					// URL doesn't contain valid id. Redirect to error page
					header("location: error.php");
					exit();
				}
                
			} else{
				echo "Error in SSN while updating";
			}
		
		}
			// Close statement
			mysqli_stmt_close($stmt);
        
			// Close connection
			mysqli_close($link);
	}  else{
        // URL doesn't contain id parameter. Redirect to error page
        header("location: error.php");
        exit();
	}	
}
?>
 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Company DB</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        .wrapper{
            width: 500px;
            margin: 0 auto;
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-12">
                    <div class="page-header">
                        <h3>Update Dependent for SSN =  <?php echo $_GET["Ssn"]; ?> </H3>
                    </div>
                    <p>Please edit the input values and submit to update.
                    <form action="<?php echo htmlspecialchars(basename($_SERVER['REQUEST_URI'])); ?>" method="post">
                    <div class="form-group <?php echo (!empty($Dname_err)) ? 'has-error' : ''; ?>">
                            <label>Dependent's Name</label>
                            <input type="text" name="Dname" class="form-control" value="<?php echo $Dname; ?>">
                            <span class="help-block"><?php echo $Dname_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Relationship_err)) ? 'has-error' : ''; ?>">
                            <label>Relationship</label>
                            <input type="text" name="Relationship" class="form-control" value="<?php echo $Relationship; ?>">
                            <span class="help-block"><?php echo $Relationship_err;?></span>
                        </div>
						<div class="form-group <?php echo (!empty($Sex_err)) ? 'has-error' : ''; ?>">
                            <label>Sex</label>
                            <input type="text" name="Sex" class="form-control" value="<?php echo $Sex; ?>">
                            <span class="help-block"><?php echo $Sex_err;?></span>
                        </div>            
						<div class="form-group <?php echo (!empty($Birth_err)) ? 'has-error' : ''; ?>">
                            <label>Birth date</label>
                            <input type="date" name="Bdate" class="form-control" value="<?php echo date('Y-m-d'); ?>">
                            <span class="help-block"><?php echo $Birth_err;?></span>
                        </div>						
                        <input type="hidden" name="Ssn" value="<?php echo $Ssn; ?>"/>
                        <input type="submit" class="btn btn-primary" value="Submit">
                        <a href="index.php" class="btn btn-default">Cancel</a>
                    </form>
                </div>
            </div>        
        </div>
    </div>
</body>
</html>
