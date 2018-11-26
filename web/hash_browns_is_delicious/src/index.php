<html>
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head>

<?php
if (isset($_GET['view-source']))
{
    highlight_file(__FILE__) and die();
}
if (isset($_GET['md5']) && isset($_GET['sha1']))
{
    $inp1 = $_GET['md5'];
    $inp2 = $_GET['sha1'];
    $md5 = md5($inp1);
    $sha1 = sha1($inp2);

    $success1 = false;
    $success2 = false;
    if($inp1 == $md5)
    {
        echo "<p>2^128 분의 1의 확률을 맞추다니??</p>";
        $success1 = true;
    }
    if($inp2 == $sha1)
    {
        echo "<p>2^160 분의 1의 확률을 맞추다니???</p>";
        $success2 = true;
    }

    if ($success1 && $success2)
    {
        require "flag.php";
    }
    else
    {
        echo "<p><strong>FAIL</strong></p>";
    }
}
?>
<p>MD5와 SHA1이 취약한 해시 알고리즘이라는 것은 잘 알려져 있다. 그렇다면 어디 한번 공격해볼까?</p>
<form>
    <label>MD5: </label>
    <input type='text' name='md5' />
    <label>SHA1: </label>
    <input type='text' name='sha1' />
    <input type='submit' />
</form>

<a href='?view-source'>Source Code</a>

</html>
