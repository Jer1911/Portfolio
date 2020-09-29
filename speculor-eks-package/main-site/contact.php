<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Speculor Consulting - Contact Us</title>
	<link href="css/bootstrap-4.4.1.css" rel="stylesheet">
	<script src="js/jquery-3.4.1.min.js"></script>
  </head>
  <body>
	  
	  <!--Import Navigation Bar:-->
  <div id="nav_bar"></div>
  <script>
		$(function(){
			$("#nav_bar").load("NavBar.html");
		});
</script>

<div class="container-fluid px-0">
	<div class="card overflow-hidden border-0 rounded-0 text-left">
		<img src="images/9.jpg" class="card-img rounded-0" alt="Speculor Consulting Image">
		<div class="card-img-overlay d-flex flex-column justify-content-center">
			<h2 class="card-title text-white">Contact Us</h2>
		</div>
	</div>
</div>	  
	  
<!--Begin Page Content-->
<?php
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;
require 'vendor/autoload.php';
	  
// ReCaptcha: -----------------------------------------------------------------
require_once("vendor/google/recaptcha/src/autoload.php");
$secret = getenv('recapSecretKey');
//$secret = ""; // DEBUG - fill with appropriate value for testing.
$response;
// ----------------------------------------------------------------------------

$sender = 'help@speculorconsulting.com';
$recipient = 'help@speculorconsulting.com';
$host = 'email-smtp.us-west-2.amazonaws.com';
$port = 587;
$subject = 'Email Form Submission';

$client_name = '';	  
$email_address = '';
$phone = '';
$company = '';
$job_title = '';
$message = '';
$recruiter = '';
$hiring_manager = '';

$email_error = '';
$client_name_error = '';
$company_error = '';
$job_title_error = '';
$recruiter_error = '';
$hiring_manager_error = '';

$mail = new PHPMailer(true);
// $mail->SMTPDebug = 2; //DEBUG
	  
function test_input($data)
{
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}
	  
function concatinate_message($client_name, $email_address, $phone, $company, $job_title, $message, $recruiter, $hiring_manager)
{
	$message = sprintf("Name: %s\nEmail: %s\nPhone: %s\nCompany: %s\nJob Title: %s\n\nMessage:\n%s\n\nRecruiter: %s\nHiring Manager: %s\n", $client_name, $email_address, $phone, $company, $job_title, $message, $recruiter, $hiring_manager);
	return $message;
}
	  
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	// EMAIL:
	if (empty($_POST["email_address"]))
	{
		$email_error = "Email is required";
	}
	else
	{
		$email_address = test_input($_POST["email_address"]);		
		//echo "email_address value: " . $email_address . "<br>"; //DEBUG		
		if (!filter_var($email_address, FILTER_VALIDATE_EMAIL))
		{
			$email_error = "Invalid email format";
		}
	}
	
	// MESSAGE:
	if (empty($_POST["message"]))
	{
		$message = "";
	}
	else
	{
		$message = test_input($_POST["message"]);		
		//echo "message value: " . $message . "<br>"; //DEBUG
	}
	
	// NAME:
	if (empty($_POST["client_name"]))
	{
		$client_name_error = "Name is required";
	}
	else
	{
		$client_name = test_input($_POST["client_name"]);
		if (!preg_match("/^[a-zA-Z ]*$/",$client_name))
		{
			$client_name_error = "Only letters and white space allowed";
    	}
		//echo "client_name value: " . $client_name . "<br>"; //DEBUG
	}
	
	// COMPANY:
	if (empty($_POST["company"]))
	{
		$company_error = "Company is required";
	}
	else
	{
		$company = test_input($_POST["company"]);		
		//echo "company value: " . $company . "<br>"; //DEBUG
	}
	
	// PHONE:
	if (empty($_POST["phone"]))
	{
		$phone = "";
	}
	else
	{
		$phone = test_input($_POST["phone"]);		
		//echo "phone value: " . $phone . "<br>"; //DEBUG
	}
	
	// JOB TITLE:
	if (empty($_POST["job_title"]))
	{
		$job_title_error = "Job Title is required";
	}
	else
	{
		$job_title = test_input($_POST["job_title"]);		
		//echo "job_title value: " . $job_title . "<br>"; //DEBUG
	}
	
	// RECRUITER:
	if (empty($_POST["recruiter"]))
	{
		$recruiter_error = "Checkbox is required";
	}
	else
	{
		$recruiter = test_input($_POST["recruiter"]);
	}
	
	// HIRING MANAGER:
	if (empty($_POST["hiring_manager"]))
	{
		$hiring_manager_error = "Checkbox is required";
	}
	else
	{
		$hiring_manager = test_input($_POST["hiring_manager"]);
	}
	
	// ReCaptcha: -------------------------------------------------------------
	if (isset($_POST["g-recaptcha-response"]))
	{
		$recaptcha = new \ReCaptcha\ReCaptcha($secret, new \ReCaptcha\RequestMethod\SocketPost());		
		$response = $recaptcha->verify($_POST['g-recaptcha-response'], $_SERVER['REMOTE_ADDR']);
		//var_dump($response); //DEBUG
	}
	//-------------------------------------------------------------------------
	
	if ($response->isSuccess())
	{
		try
		{
			$message = concatinate_message($client_name, $email_address, $phone, $company, $job_title, $message, $recruiter, $hiring_manager);

			$mail->isSMTP();
			$mail->setFrom($sender);

			$mail->Username   = getenv('usernameSmtp');
			$mail->Password   = getenv('passwordSmtp');
			//$mail->Username   = ""; // DEBUG - fill with appropriate values for testing.
			//$mail->Password   = ""; // DEBUG - fill with appropriate values for testing.
			
			$mail->Host       = $host;
			$mail->Port       = $port;
			$mail->SMTPAuth   = true;
			$mail->SMTPSecure = 'tls';

			$mail->addAddress($recipient);

			$mail->isHTML(false);
			$mail->Subject    = $subject;
			$mail->Body       = $message;

			$mail->Send();
			echo "Email sent!" , PHP_EOL;
		}
		catch (phpmailerException $e)
		{
			echo "phpmailerException:";
			echo "An error occurred. {$e->errorMessage()}", PHP_EOL;
		}
		catch (Exception $e)
		{
			echo "Exception:";
			echo "Email not sent. {$mail->ErrorInfo}", PHP_EOL;
		}
	}
	else
	{
		$recaptcha_error = $response->getErrorCodes();
		echo "ReCaptcha Error Occured. Please go back and try again.";
		//echo '<pre>'; print_r($recaptcha_error); echo '</pre>'; // DEBUG		
	}
}
?>
  
<div class="container-fluid pt-5 pb-5" style="background-color:gray; color:white">
	<form action="contact.php" method="POST">
		
		<div class="row">
			<div class="col-sm-4">Name:</div>
			<div class="col-sm-8">
				<input type="text" name="client_name" value="<?php echo $client_name;?>" style="background-color:black; color:greenyellow">
				<span class="error">* <?php echo $client_name_error;?></span>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Email Address:</div>
			<div class="col-sm-8">
				<input type="text" name="email_address" value="<?php echo $email_address;?>" style="background-color:black; color:greenyellow">
				<span class="error">* <?php echo $email_error;?></span>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Phone Number (optional):</div>
			<div class="col-sm-8">
				<input type="text" name="phone" value="<?php echo $phone;?>" style="background-color:black; color:greenyellow">
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Company:</div>
			<div class="col-sm-8">
				<input type="text" name="company" value="<?php echo $company;?>" style="background-color:black; color:greenyellow">
				<span class="error">* <?php echo $company_error;?></span>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Job Title:</div>
			<div class="col-sm-8">
				<input type="text" name="job_title" value="<?php echo $job_title;?>" style="background-color:black; color:greenyellow">
				<span class="error">* <?php echo $job_title_error;?></span>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Message:</div>
			<div class="col-sm-8">
				<textarea name="message" cols="30" rows="12" style="background-color:black; color:greenyellow"><?php echo $message;?></textarea>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Are you a recruiting agency?</div>
			<div class="col-sm-8">
				<input type="radio" name="recruiter" value="no">no
				<input type="radio" name="recruiter" value="yes">yes
				<span class="error">* <?php echo $recruiter_error; ?></span>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4">Are you a hiring manager?</div>
			<div class="col-sm-8">
				<input type="radio" name="hiring_manager" value="no">no
				<input type="radio" name="hiring_manager" value="yes">yes
				<span class="error">* <?php echo $hiring_manager_error; ?></span>
				<br><br>
			</div>
		</div>

		<div class="row">
			<div class="col-sm-4"></div>
			<div class="col-sm-8">
				<div class="g-recaptcha" data-sitekey="REDACTED" data-theme="dark"></div>
				<br><br>
			</div>
		</div>
		
		<div class="row">
			<div class="col-sm-4"></div>
			<div class="col-sm-8">
				<input name="Button1" type="submit" value="Send" title="">
			</div>
		</div>

	</form>
	<script src='https://www.google.com/recaptcha/api.js'></script>
</div>

	  
<!--End Page Content-->
	  
	  <script src="js/jquery-3.4.1.min.js"></script>
	  <script src="js/bootstrap-4.4.1.js"></script>
  </body>
</html>
