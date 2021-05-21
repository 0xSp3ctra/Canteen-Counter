<html>
<body>

	<?php

	$dbname = '';
	$dbuser = '';  
	$dbpass = ''; 
	$dbhost = '';

	$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

	if(!$connect){
		echo "Error: " . mysqli_connect_error();
		exit();
	}

	echo "Connection Success!<br><br>";

	$Passage = $_GET["Passage"]; 

	$query = "INSERT INTO Projet(Passage) VALUES ('$Passage')";
	$result = mysqli_query($connect,$query);

	echo "Insertion Success!<br>";

	?>
</body>
</html>