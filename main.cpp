#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <functional>

//COMP322 Winter 2023 ; Assignment 3 Hugo Belzil

//Node structure implemented for the Linked List
struct Node {
    std::string content_file;
    std::size_t hash_value;
    Node* next;
};

// Implementation of our Linked List
class LinkedList {
public:

    Node* head;

    LinkedList() {
        head = NULL;
    }

    //We use the implementation of this method to add a version of a file in our linked list
    void addNode(std::string content_file, std::size_t value) {
        Node* newNode = new Node;
        newNode->content_file = content_file;
        newNode->hash_value = value;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    //This method is used multiple times to get the number of versions stored in
    //the linked list by the user
    int number_of_versions(){
        int counter=0;
        if (head==NULL){
            return counter;
        }
        Node* curr=head;
        counter++;
        while(curr->next!=NULL){
            counter++;        //we increment this counter everytime we traverse a node in the list
            curr=curr->next;
        }
        return counter;
    }

};
//this is the class corresponding to part1 of the assignment
class Git322{
public:
    LinkedList mylist;
    Git322(){
        mylist=LinkedList();
    }
    void compare(int version1, int version2);
    void search(std::string keyword);
    void remove(int version);
    void load();
    void print();
    void add();
    //note that I put the function hash in public because in assignment 2,
    //it was not a helper
    std::size_t  hash_it(std::string someString);


private:
    //PLEASE MODIFY THIS STRING IN FUNCTION OF THE LOCATION OF YOUR TXT FILE
    std::string FILENAME = "./txt_folder/file1.txt";

    //helper functions
    bool helper_check_presence_keyword(std::string keyword);
    std::vector<std::string> helper_get_lines_of_cf(const std::string &file_content);


};

//please find the implementations of the methods used in assignment 2.
//No modifications were brought to the methods except the name of the list linked has changed
//and the methods are now part of the class Git322 and EnhancedGit322
void Git322::compare(int version1, int version2) {
    if (version1 > mylist.number_of_versions() || version2 > mylist.number_of_versions()) {
        std::cout << "Please enter valid numbers.\n" << std::endl;
        return;
    }
    //the following 12 lines are here to spot which nodes correspond to the version numbers the user selected
    Node *v1_node = mylist.head;
    Node *v2_node = mylist.head;
    int get_v1_node = 1;
    int get_v2_node = 1;
    while (get_v1_node != version1) {
        v1_node = v1_node->next;
        get_v1_node++;
    }
    while (get_v2_node != version2) {
        v2_node = v2_node->next;
        get_v2_node++;
    }
    //We create two vectors containing all the lines of the 2 versions we have to compare
    std::vector<std::string> all_vectors_fc1 = helper_get_lines_of_cf(v1_node->content_file);
    std::vector<std::string> all_vectors_fc2 = helper_get_lines_of_cf(v2_node->content_file);

    //get the smallest vector
    int size_fc1 = all_vectors_fc1.size();
    int size_fc2 = all_vectors_fc2.size();

    if (size_fc1 == size_fc2) { //case where both files have the same number of lines
        for (int i = 0; i < size_fc1; i++) {
            if (all_vectors_fc1[i] == "" && all_vectors_fc2[i] != "") {
                std::cout << "Line " << i+1 << ": " << " <Empty line> <<>> " << all_vectors_fc2[i] << std::endl;
                continue;
            }
            if (all_vectors_fc1[i] != "" && all_vectors_fc2[i] == "") {
                std::cout << "Line " << i+1 << ": " << all_vectors_fc1[i] << " <<>> Empty line "<<"\n"<<std::endl;
                continue;
            }
            else{
                if (all_vectors_fc1[i]!= all_vectors_fc2[i]){
                    std::cout<<"Line "<<i+1<<": "<<all_vectors_fc1[i]<<" <<>> "<<all_vectors_fc2[i]<<"\n"<<std::endl;
                    continue;
                }
                else{
                    std::cout<<"Line "<<i+1<<": <Identical>"<<std::endl;
                    continue;
                }
            }
        }
        std::cout<<"\n"<<std::endl;
        return;
    }
    if (size_fc2>size_fc1){ //case where the second file has more lines than the first file
        for (int i=0;i<size_fc1;i++){
            if (all_vectors_fc1[i] == "" && all_vectors_fc2[i] != "") {
                std::cout << "Line " << i+1 << ": " << " <Empty line> <<>> " << all_vectors_fc2[i] << std::endl;
                continue;
            }
            if (all_vectors_fc1[i] != "" && all_vectors_fc2[i] == "") {
                std::cout << "Line " << i+1 << ": " << all_vectors_fc1[i] << " <<>> Empty line "<<"\n"<<std::endl;
                continue;
            }
            else{
                if (all_vectors_fc1[i]!= all_vectors_fc2[i]){
                    std::cout<<"Line "<<i+1<<": "<<all_vectors_fc1[i]<<" <<>> "<<all_vectors_fc2[i]<<"\n"<<std::endl;
                    continue;
                }
                else{
                    std::cout<<"Line "<<i+1<<": <Identical>"<<"\n"<<std::endl;
                    continue;
                }
            }
        }
        for (int i=size_fc1;i<size_fc2;i++){
            std::cout<<"Line "<<i+1<<": "<<" <<>> END OF FILE REACHED <<>> "<<all_vectors_fc2[i]<<"\n"<<std::endl;
            continue;
        }
    }

    if (size_fc1>size_fc2){// case where the first file has more lines than the second one
        for (int i=0;i<size_fc2;i++){
            if (all_vectors_fc1[i] == "" && all_vectors_fc2[i] != "") {
                std::cout << "Line " << i+1 << ": " << " <Empty line> <<>> " << all_vectors_fc2[i] << std::endl;
                continue;
            }
            if (all_vectors_fc1[i] != "" && all_vectors_fc2[i] == "") {
                std::cout << "Line " << i+1 << ": " << all_vectors_fc1[i] << " <<>> Empty line "<<"\n"<<std::endl;
                continue;
            }
            else{
                if (all_vectors_fc1[i]!= all_vectors_fc2[i]){
                    std::cout<<"Line "<<i+1<<": "<<all_vectors_fc1[i]<<" <<>> "<<all_vectors_fc2[i]<<"\n"<<std::endl;
                    continue;
                }
                else{
                    std::cout<<"Line "<<i+1<<": <Identical>"<<"\n"<<std::endl;
                    continue;
                }
            }
        }
        for (int i=size_fc2;i<size_fc1;i++){
            std::cout<<"Line "<<i+1<<": "<<all_vectors_fc1[i]<<" <<>> END OF FILE REACHED\n"<<std::endl;
            continue;
        }
    }
}

void Git322::search(std::string keyword) {
    if (!helper_check_presence_keyword(keyword)){ //using the helper
        std::cout<<"The keyword '"<<keyword<<"' was not found in any version. \n"<<std::endl;
        return;
    }
    //this line is reached in the case where keyword was found
    std::cout<<"The keyword '"<<keyword<<"' has been found in the following versions: "<<std::endl;
    Node* current = mylist.head;
    int iterat=1;
    //we traverse every node of the linked list
    while (current != NULL) {
        std::istringstream extractor(current->content_file);
        std::string word;
        while (extractor >> word) { //we compare all the words of the txt content of each node with the keyword
            if (word == keyword) {
                std::cout<<"Version number : "<<iterat<<std::endl; //if keyword was found, we print the version content
                std::cout<<"Hash Value : "<<current->hash_value<<std::endl;
                std::cout<<"Content : "<<current->content_file<<"\n"<<std::endl;
                break;
            }
            //we check if the last character of a word is a punctuation or not
            //if not, then we remove the punctuation and then compare it with the keyword
            if(!std::isalpha(word.back())){
                word.pop_back();
                if (keyword == word) {
                    std::cout<<"Version number : "<<iterat<<std::endl; //if keyword was found, we print the version content
                    std::cout<<"Hash Value : "<<current->hash_value<<std::endl;
                    std::cout<<"Content : "<<current->content_file<<"\n"<<std::endl;
                    break;
                }
            }
        }
        iterat++;
        current = current->next;
    }
    return;
}

std::vector<std::string> Git322::helper_get_lines_of_cf(const std::string &file_content) {
    std::istringstream extract(file_content);
    std::vector<std::string> lines_of_content_file;
    std::string line;
    while (getline(extract, line)) {
        lines_of_content_file.push_back(line);
    }
    return lines_of_content_file;
}

bool Git322::helper_check_presence_keyword(std::string keyword) {
    Node* current = mylist.head;
    while (current != NULL) { //this first while loop traverses all the nodes of the linked list
        std::istringstream extractor(current->content_file);
        std::string word;
        while (extractor >> word) {  //this second while loop compares every word of the node visited by the while loop
            if (word == keyword) {
                return true; //if the word is found even only once, we return true and dont need to visit the rest of the nodes
            }
        }
        current = current->next;
    }
    return false;
}

std::size_t Git322::hash_it(std::string someString) {
    std::size_t hashed_value = std::hash<std::string>{}(someString);
    return hashed_value;
}

void Git322::add() {
    std::ifstream fs1(FILENAME);
    std::string line;
    std::string txt_content = "";

    //This snippet fills the string corresponding to the text in file 1
    while (std::getline(fs1, line)) {
        if (line.empty()) {
            txt_content += "\n"; //IMPORTANT : WE HAVE TO CONSIDER EMPTY LINES IN THE STRING
        }
        if (fs1.eof()){
            txt_content+=line;
            break;
        }
        else{
            txt_content += line;
            txt_content += "\n";
        }
    }

    if (mylist.head == NULL) {
        mylist.addNode(txt_content, hash_it(txt_content));
        std::cout<<"Your content has been added successfully \n"<<std::endl;
        return;
    }
    /*In this while loop, we traverse every node and check whether
     there is already a node that contains the txt version of the file or not*/
    Node *curr = mylist.head;
    while (curr!=NULL) {
        if (curr->hash_value == hash_it(txt_content)) {
            std::cout << "GIT322 did not detect any change to your file and will not create a new version \n"<< std::endl;
            return;
        }
        curr = curr->next;
    }

    //this line is reached if the content was not found, and we add the content
    mylist.addNode(txt_content, hash_it(txt_content));
    std::cout<<"Your content has been added successfully \n"<<std::endl;
    return;
}

void Git322::remove(int version) {
    if (version==1 && mylist.number_of_versions()==1){
        delete mylist.head;
        mylist.head=NULL;
        std::cout<<"Version 1 deleted successfully.\n"<<std::endl;
        return;
    }
    if (version==1){ // edge case where we have to remove the head of the LL
        Node* temp=mylist.head->next;
        delete mylist.head;
        mylist.head=temp;
        std::cout<<"Version 1 deleted successfully.\n"<<std::endl;
        return;
    }
    //Edge case where the tail is removed from the LL
    if (version==mylist.number_of_versions()){
        int counter=1;
        Node* prev=mylist.head;
        while (counter!=mylist.number_of_versions()-1){
            prev=prev->next;
            counter++;
        }
        delete prev->next;
        prev->next=NULL;
        std::cout<<"Version "<<mylist.number_of_versions()<<" deleted successfully.\n"<<std::endl;
        return;
    }
    else{ //case whre the node removed is neither the tail nor the head
        Node* curr;
        Node* prev=mylist.head;
        int counter=1; //this counter is used to traverse the list and spot which node has to be removed
        while (counter!=version-1){
            prev=prev->next;
            counter++;
        }
        curr=prev->next;
        prev->next=curr->next;
        delete curr;
        std::cout<<"Version "<<version<<" deleted successfully.\n"<<std::endl;
        return;
    }
}

void Git322::load() {
    std::cout<<"\n"<<"Which version would you like to load ? "<<std::endl;
    int v_to_load;
    std::cin>>v_to_load; //get the number of the version from the user

    //if the version number is unvalid, we recursively call the function and tell the user how many versions exist
    if (v_to_load>mylist.number_of_versions() || v_to_load<=0 ){
        std::cout<<"Please enter a valid version number. There are "<<mylist.number_of_versions()<<" versions available."<<std::endl;
        return load();
    }
    else{
        int counter=1;
        Node* version_getter=mylist.head;

        /*this following snippet is written so that we traverse the linked list and every time
        a node is traversed, we increment an integer basically set to be 1. the loop stops when the pointer
         node getter points to the n-th node, which we want to load*/
        while (counter!=v_to_load){
            version_getter=version_getter->next;
            counter++;
        }

        //we open the txt file
        std::ofstream file_writer;
        file_writer.open(FILENAME);
        file_writer<<version_getter->content_file<<std::endl; //we write to the txt file of the node
        file_writer.close();
        return;
    }
}


void Git322::print() {
    std::cout<<"Number of versions : "<<mylist.number_of_versions()<<"\n"<<std::endl;
    Node* curr=mylist.head;
    int counter=1;

    if (mylist.number_of_versions()==1){
        std::cout<<"Version number : "<<counter<<std::endl;
        std::cout<<"Hash Value : "<<curr->hash_value<<std::endl;
        std::cout<<"Content : "<<curr->content_file<<"\n"<<std::endl;
        return;
    }

    while (curr!=NULL){
        std::cout<<"Version number : "<<counter<<std::endl;
        std::cout<<"Hash Value : "<<curr->hash_value<<std::endl;
        std::cout<<"Content : "<<curr->content_file<<"\n"<<std::endl;
        curr=curr->next;
        counter++;
    }
}

//Here follows the implementation of the class required in the second part of the assignment
//it inherits the class Git322
class EnhancedGit322 : public Git322 {
public:
    //
    std::string file_name_save = "./txt_folder/save_versions.txt";
    //we implement this function to save the versions in the linked list when the user exits the program
    void save_versions();
    //we use this method in the constructor to load the previous versions in the constructor
    void load_previous_versions();
    //the constructor is made so that it loads all the previous versions in the linked list attribute
    EnhancedGit322(){
        load_previous_versions(); //see implementation
    }

};

//Everytime the user exits the program, we loop thru the linked list and for every version, we copy its file content
//into a txt file named save_versions.txt saved in the same folder as file1.txt which is used as a copy of all our versions
//Note that we delimit each version by using the character: "-%&**Delimitation**&%-"
//see implementation of the interactive user loop
void EnhancedGit322::save_versions() {
    std::ofstream versions_save_writer;
    versions_save_writer.open(file_name_save);
    Node* curr=mylist.head;
    while(curr!=NULL){
        versions_save_writer<<curr->content_file<<std::endl;
        versions_save_writer<<"-%&**Delimitation**&%-"<<std::endl; //uncommon character
        curr=curr->next;
    }
}
//this function is used in the constructor. it reads thru the file save_versions.txt
//in order to retrieve all the previous versions saved by the user
void EnhancedGit322::load_previous_versions() {
    std::ifstream versions_reader(file_name_save);
    std::string line;
    std::string content_accumulator="";

    while (std::getline(versions_reader,line)){
        if (line=="-%&**Delimitation**&%-"){
            mylist.addNode(content_accumulator, hash_it(content_accumulator));
            content_accumulator=""; //we reset the content file after we reach the end of a version
            continue;
        }
        if (versions_reader.eof()){
            mylist.addNode(content_accumulator, hash_it(content_accumulator));
            //if we reached the end of the last version, we exit the function
            break;
        }
        else{
            content_accumulator+=line;
            content_accumulator+="\n";
        }
    }
}


int main() {
    //This is the implementation of the interactive loop.

    EnhancedGit322 tracker;

    std::cout << "Welcome to the 322 file versioning system!" << std::endl;
    std::cout << "---------" << std::endl;
    while (true){
        char user_inp;
        std::cout << "To add the content of your file to version control, press 'a'" << std::endl;
        std::cout << "To remove a version, press 'r' " << std::endl;std::cout << "To load a version, press 'l' " << std::endl;
        std::cout << "To print to the screen the detailed list of all versions press 'p' " << std::endl;
        std::cout << "To compare any 2 versions press 'c' " << std::endl;
        std::cout << "To search versions for a keyword press 's' " <<std::endl;
        std::cout << "To exit press 'e' \n" << std::endl;
        std::cin>> user_inp;

        if (user_inp=='e'){
            std::cout<<"Goodbye !"<<std::endl;
            tracker.save_versions();
            break;
        }
        if (user_inp=='a'){
            tracker.add(); //add
            continue;
        }
        if (user_inp=='p'){
            tracker.print();
            continue;
        }
        if (user_inp=='l'){
            tracker.load();
            continue;
        }
        if (user_inp=='r'){
            int vr_to_remove;
            std::cout<<"Enter the number of the version you want to delete : "<<std::endl;
            std::cin>>vr_to_remove;
            if (vr_to_remove>tracker.mylist.number_of_versions()  || vr_to_remove<=0){
                std::cout<<"Invalid number."<<std::endl;
                std::cout<<"The menu will appear again. Press 'r' again and select a valid number.\n"<<std::endl;
                continue;
            }
            else{
                tracker.remove(vr_to_remove);
            }
        }
        if (user_inp=='s'){
            std::cout<<"Please enter the keyword : "<<std::endl;
            std::string kw;
            std::cin>>kw;
            tracker.search(kw);
            continue;
        }
        if (user_inp=='c'){
            std::cout<<"Please enter the number of the first version to compare. "<<std::endl;
            int v1;
            std::cin>>v1;
            std::cout<<"Please enter the number of the second version to compare. "<<std::endl;
            int v2;
            std::cin>>v2;
            tracker.compare(v1,v2);
            continue;
        }
    }

    return 0;
}

//END OF ASSIGNMENT3
