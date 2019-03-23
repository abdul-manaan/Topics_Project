// 500 MB
var x = [];

function grow() {
	
		let arr = Array(1024*1024/16*500).fill(" ")
		x.concat(arr);
		arr.reverse();
		// createSomeNodes();
    	// setTimeout(grow,5000);
}

grow();