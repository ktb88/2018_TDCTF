<?php
@session_set_cookie_params(36000);
@session_start();

@require_once dirname(__FILE__)."/classes.php";
@require_once dirname(__FILE__)."/config.php";

if (@$_POST['name']) {
	@$_SESSION['link'] = @array('name' => @htmlspecialchars(@$_POST['name']), 'time' => @time());
	@die("<script type='text/javascript'>location.href='.';</script>");
}
if (!@$_SESSION['link']['name']) {
	if (!@$_SESSION['link']['real_first?']) {
		@$_SESSION['link']['real_first?'] = true;
		@die("<script type='text/javascript'>location.href='.';</script>");
	}
	@die(@file_get_contents(@dirname(__FILE__).'/templates/set.html'));
}
if (!isset($_SESSION['link'][$_SESSION['link']['name']."_tail"])) {
	@$_SESSION['link'][@$_SESSION['link']['name']."_tail"] = 0;
	@die("<script type='text/javascript'>location.reload();</script>");
}
if (@$_SESSION['link']['name']) @$obj = new LinkList();
if (@$_GET['p'] == 'reset') {
	unset($_SESSION['link']);
	@die("<script type='text/javascript'>location.reload();</script>");
}
if (@$_SESSION['link'][@$_SESSION['link']['name']."_list"]) {
	@$arr = @json_decode(@$_SESSION['link'][@$_SESSION['link']['name']."_list"]);
	for(@$i=0;@$i<count(@$arr);@$i++){
		@$obj->insert(@$arr[@$i], @$i);
	}
}
if (@$_GET['p'] == 'raw') {
	@header("Content-Type: text/plain");
	@die(@$_SESSION['link'][@$_SESSION['link']['name']."_list"]);
}
if (@$_SESSION['link']['admin_only_list']) {
	unset($_SESSION['link']);
	die("<script type='text/javascript'>alert('GJ!!! The first flag is ".@addslashes(@$flag1)."');location.href='.';</script>");
	admin:
		if ($_POST['value'] && $_POST['key']) {
			@$obj->insert(@$_GET['value'], @$_POST['key']);
			@$arr[@$_POST['key']] = @$_GET['value'];
			@$_SESSION['link'][@$_SESSION['link']['name']."_list"] = @json_encode(@$arr);
		}
}
if (@$_SESSION['link'][@$_SESSION['link']['name']."_tail"] > 0xff) {
	unset($_SESSION['link']);
	@die("<script type='text/javascript'>alert('Realrudaganya?!?!? The second flag is ".@addslashes(@$flag2)."');location.href='.';</script>");
}
if (!@$_GET['p'] || $_GET['p'] == '') {
	@$content = @file_get_contents(@dirname(__FILE__).'/templates/login.html');
	@$content = @str_replace('$name', @$_SESSION['link']['name'], @$content);
	if (@$_SESSION['link'][@$_SESSION['link']['name']."_list"] || @$data='') {
		@$r = @$obj->readList();
		@$data = '<pre>linked list: '.PHP_EOL;
		for(@$i=0;@$i<count(@$r);@$i++){
			@$data .= "No.".(@$i+1).": ".@$r[@$i].PHP_EOL;
		}
		@$data .= '</pre>';
	}
	@$content = str_replace('$content', @$data, @$content);
	die(@$content);
}
if (@$_GET['p'] == 'insert' && isset($_GET['value'])) {
	if (@$arr[100]) die("<script type='text/javascript'>alert('Too many linked-list! Get out!');location.href='.';</script>");
	if (@$_SESSION['link'][@$_SESSION['link']['name']."_tail"] == 0) @$obj->insertFirst(@htmlspecialchars(@$_GET['value']));
	else @$obj->insert(@$_GET['value'], @$_SESSION['link'][@$_SESSION['link']['name']."_tail"]);
	@$_SESSION['link'][@$_SESSION['link']['name']."_tail"]++;
	@$arr[@$_SESSION['link'][@$_SESSION['link']['name']."_tail"]-1] = @htmlspecialchars(@$_GET['value']);
	@$_SESSION['link'][@$_SESSION['link']['name']."_list"] = @json_encode(@$arr);
	die("<script type='text/javascript'>location.href='.';</script>");
}
if (@$_GET['p'] == 'insert_first' && isset($_GET['value'])) {
	@$obj->insertFirst(@htmlspecialchars(@$_GET['value']));
	@$_SESSION['link'][@$_SESSION['link']['name']."_tail"]++;
	@$arr[0] = @htmlspecialchars(@$_GET['value']);
	@$_SESSION['link'][@$_SESSION['link']['name']."_list"] = @json_encode(@$arr);
	@die("<script type='text/javascript'>location.href='.';</script>");
}
if ($_GET['p'] == 'delete' && isset($_GET['key'])) {
	if (!@$arr[0]) @$arr[0] = '';
	@$obj->deleteNode(@$_GET['key']);
	unset($arr[@$_GET['key']]);
	#@$_SESSION['link'][@$_SESSION['link']['name']."_tail"] = (int)@$_GET['key'] & 0x7fffffff;
	#@$_SESSION['link'][@$_SESSION['link']['name']."_tail"]--;
	@$_SESSION['link'][@$_SESSION['link']['name']."_list"] = json_encode(@$arr);
	@die("<script type='text/javascript'>location.href='.';</script>");
}
