var hidden = false;
function getElementsByClass(searchClass, domNode, tagName) {
	if (domNode == null) domNode = document;
	if (tagName == null) tagName = '*';
	var el = new Array();
	var tags = domNode.getElementsByTagName(tagName);
	var tcl = " "+searchClass+" ";
	for(i=0,j=0; i<tags.length; i++) {
		var test = " " + tags[i].className + " ";
		if (test.indexOf(tcl) != -1)
		el[j++] = tags[i];
	}
	return el;
}

function toggle_chk_true(source) {
  checkboxes = document.getElementsByName('foo');
  for(var i=0, n=checkboxes.length;i<n;i++) {
    checkboxes[i].checked = true;

    toggle_hideme2(checkboxes[i].value,'block');
  }
}

function toggle_chk_false(source) {
  checkboxes = document.getElementsByName('foo');
  for(var i=0, n=checkboxes.length;i<n;i++) {
    checkboxes[i].checked = false;

    toggle_hideme2(checkboxes[i].value,'none');
  }
}
 
function toggle_hideme(name)
{

	var hellos = getElementsByClass(name, null);

	var nodeList = document.getElementsByClassName(name);

	hidden = !hidden;
	var newDisplay;
	var e = document.getElementById(name);

	if(e.style.display == 'none')
	{
		newDisplay = 'inline';
	}
	else
	{
		newDisplay = 'none';
	}
	
	for(var i = 0; i < hellos.length; i++)
	{

		hellos[i].style.display = newDisplay;
	}
}

function toggle_hideme2(name,status)
{

	var hellos = getElementsByClass(name, null, "div");

	var nodeList = document.getElementsByClassName(name);

	
	for(var i = 0; i < hellos.length; i++)
	{

		hellos[i].style.display = status;
	}
}
