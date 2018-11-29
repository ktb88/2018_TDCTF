<?php
class ListNode {
	public $data;
	public $next;

	function __construct($data){
		$this->data = $data;
		$this->next = NULL;
	}

	function readNode(){
		return $this->data;
	}
}

class LinkList {
	private $firstNode;
	private $lastNode;
	private $count;

	function __construct(){
		$this->firstNode = NULL;
		$this->lastNode = NULL;
		$this->count = 0;
	}

	public function insertFirst($data){
		$link = new ListNode($data);
		$link->next = $this->firstNode;
		$this->firstNode = &$link;

		if ($this->lastNode == NULL) $this->lastNode = &$link;
		$this->count++;
	}


	public function readList(){
		$listData = array();
		$current = $this->firstNode;

		while($current != NULL){
			array_push($listData, $current->readNode());
			$current = $current->next;
		}
		$i = 0;
		$return = array();
		foreach($listData as $v){
			$return[$i++] = $v;
		}
		return $return;
	}

	public function reverseList(){
		if ($this->firstNode != NULL) {
			if ($this->firstNode->next != NULL) {
				$current = $this->firstNode;
				$new = NULL;

				while($current != NULL){
					$temp = $current->next;
					$current->next = $new;
					$new = $current;
					$current = $temp;
				}
				$this->firstNode = $new;
			}
		}
	}

	public function deleteNode($key){
		$current = $this->firstNode;
		$previous = $this->firstNode;

		while($current->data != $key){
			if ($current->next == NULL) return NULL;
			else{
				$previous = $current;
				$current = $current->next;
			}
		}

		if ($current == $this->firstNode) {
			if ($this->count == 1) $this->lastNode = $this->firstNode;
			$this->firstNode = $this->firstNode->next;
		}else{
			if ($this->lastNode == $current) $this->lastNode = $previous;
			$previous->next = $current->next;
		}
		$this->count--;  
	}

	public function emptyList(){
		$this->firstNode == NULL;
	}

	public function insert($NewItem,$key){
		if ($key == 0) $this->insertFirst($NewItem);
		else{
			$link = new ListNode($NewItem);
			$current = $this->firstNode;
			$previous = $this->firstNode;

			for($i=0;$i<$key;$i++){       
				$previous = $current;
				$current = $current->next;
			}

			$previous->next = $link;
			$link->next = $current; 
			$this->count++;
		}
	}
}
