FamilyTree
==========
1. Person Class
 * 사람에 대한 정보를 가지고 있는 클래스입니다. `Person`에 대한 Object가 생성이되면 연계되는 `Children`의 Object도 자동으로 생성됩니다. 


2. Children Class
 * 어떠한 `Person` Object의 포인터를 가지며, 그 Object의 자식들의 정보를 `Person` Object의 *linked list*의 형태로 소유하고 있습니다. 

3. Table Class 
 * n세대만큼의 `Slot slot[n]`을 가지며 세대가 추가될 때마다 *Reallocation*이 되며 *n*의 크기가 커집니다.

4. Slot Class
 * `Children` Class가 가리키는 `parent` Object 의 `string _name` 값을 바탕으로 *hashing*하여 저장합니다. 해당 `slot`에 같은 *hash key*를 가진 `Children` Class의 Object는 *chaining* 하여 *linked list* 형태로 소유하게 됩니다.
