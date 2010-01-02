Babble

This is a demonstration of how ListMixer can be used to store 
text to a textfield.

Install it:
* ListMixer: Install and enable.
* Features: Install and enable.
* CCK: Install and enable.
  You will probably want to make sure
  you have content modules like text and nodereference enabled 
  for all of these demos.
* Enable feature: Babble Stream - a content type that has a text field.
* Enable view: 'babble'
* Go to blocks page, add 'block:Babble' to all pages.
  (Example, add to the left sidebar of garland theme on all pages.)
* Install the preset for ListMixer.*
* Create a new BabbleStream node for yourself. 


@TODO: Finish export function to export interaction and behavior settings, create a mechanism to import them.
@TODO: Would be easiest if this worked with features and maybe chaos tools but I need to learn how to do that.



*How this example works*

The view loads the current user's BabbleStream node. 

The view generated block lives on every page.

ListMixer reads a page looking for the block, if it finds it, it 
looks to the behavior library and ListMixer settings to see what 
javascript it should make available.

In this example, ListMixer adds an input field and a 
submit button to the block.

The setting is told it should update a textfield called XXX. 
@TODO still need to load up the fields for the settings.

So, a user types in the input field, hits save. 
ListMixer figures out which node it is supposed to store
data to, and then saves it to that node.


ListMixer figures out the target node in a few ways. 
By looking in the markup in the block for a node id to target.
By finding the view from the block id and loading the 
page path and the view block and searching for a node id that way.


Permissions are handled by node_save.
