<?php
    $login = trim(filter_var($_POST['login'], FILTER_SANITIZE_SPECIAL_CHARS));
    $username = trim(filter_var($_POST['username'], FILTER_SANITIZE_SPECIAL_CHARS));
    $email = trim(filter_var($_POST['email'], FILTER_SANITIZE_SPECIAL_CHARS));
    $password = trim(filter_var($_POST['password'], FILTER_SANITIZE_SPECIAL_CHARS));

    if(strlen($login) < 4) {
        echo "Упс, не работает!";
        exit;
    }

     if(strlen($username) < 2) {
        echo "Упс, имя слишком короткое!";
        exit;
    }

     if(strlen($email) < 4 && !str_contains($email, '@')) {
        echo "Упс, короткий email!";
        exit;
    }

    if(strlen($password) < 4) {
        echo "Упс, короткий пароль!";
        exit;
    }


$salt = 'ghf3h4h3uhjeh;z';
$password = md5($salt.$password);

require "db.php";

$sql = 'INSERT INTO users(login, username, email, password) VALUES(?, ?, ?, ?)';
$query = $pdo->prepare($sql);
$query->execute([$login, $username, $email, $password]);


header('Location: /');
?>