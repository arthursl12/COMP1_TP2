#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gram_exemplos.h"
#include "gram.h"

#include <vector>
#include <memory>

// TEST_CASE("FOLLOW: gramática 1"){
//     SUBCASE("Caso E e E\'"){
//         Gramatica g;
//         cria_gram_1(g);

//         // FOLLOW(E) = {$, )}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal(")"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("E");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);

//         // FOLLOW(E') = FOLLOW(E) = {$, )}
//         out.clear();
//         nt = std::make_shared<NaoTerminal>("E\'");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso T e T\'"){
//         Gramatica g;
//         cria_gram_1(g);

//         // FOLLOW(T) = FIRST(E') U FOLLOW(E') = {+,$,)}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal(")"));
//         conj_follow.insert(Terminal("+"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("T");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);

//         // FOLLOW(T') = FOLLOW(T) = {+,$,)}
//         out.clear();
//         nt = std::make_shared<NaoTerminal>("T\'");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso F"){
//         Gramatica g;
//         cria_gram_1(g);

//         // FOLLOW(F) = FIRST(T') U FOLLOW(T') = {*,+,$,)}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal(")"));
//         conj_follow.insert(Terminal("+"));
//         conj_follow.insert(Terminal("*"));


//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("F");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }

// TEST_CASE("FOLLOW: gramática 3"){
//     SUBCASE("Caso S: só o fim de palavra"){
//         Gramatica g;
//         cria_gram_3(g);

//         // FOLLOW(S) = {$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }SUBCASE("Caso A: genérico simples"){
//         Gramatica g;
//         cria_gram_3(g);

//         // FOLLOW(A) = {a,c}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("a"));
//         conj_follow.insert(Terminal("c"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("A");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }

// TEST_CASE("FOLLOW: gramática 4"){
//     SUBCASE("Caso S: só o fim de palavra"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(S) = {$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso B"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(B) = FIRST(D) U {h} = {g,f,h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("g"));
//         conj_follow.insert(Terminal("f"));
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("B");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso C"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(C) = FOLLOW(B) = {g,f,h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("g"));
//         conj_follow.insert(Terminal("f"));
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("C");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso D"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(D) = {h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("D");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso E"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(E) = FIRST(F) U FOLLOW(F) = {f,h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("f"));
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("E");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso F"){
//         Gramatica g;
//         cria_gram_4(g);

//         // FOLLOW(F) = FOLLOW(D) = {h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("F");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }

// TEST_CASE("FOLLOW: gramática 2"){
//     SUBCASE("Caso S: só o fim de palavra"){
//         Gramatica g;
//         cria_gram_2(g);

//         // FOLLOW(S) = {$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso B"){
//         Gramatica g;
//         cria_gram_2(g);

//         // FOLLOW(B) = FOLLOW(S) U {a} U FIRST(C) U FOLLOW(A) = {$,a,h,g}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal("a"));
//         conj_follow.insert(Terminal("h"));
//         conj_follow.insert(Terminal("g"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("B");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso C"){
//         Gramatica g;
//         cria_gram_2(g);

//         // FOLLOW(C) = FIRST(B) U FOLLOW(S) U {b} U FOLLOW(A) = {g,$,b,h}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal("b"));
//         conj_follow.insert(Terminal("h"));
//         conj_follow.insert(Terminal("g"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("C");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso A"){
//         Gramatica g;
//         cria_gram_2(g);

//         // FOLLOW(A) = FIRST(C) U FIRST(B) U FOLLOW(S) = {g,h,$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal("g"));
//         conj_follow.insert(Terminal("h"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("A");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }


// TEST_CASE("FOLLOW: gramática 5"){
//     SUBCASE("Caso S e A: só o fim de palavra"){
//         Gramatica g;
//         cria_gram_5(g);

//         // FOLLOW(S) = {$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);

//         // FOLLOW(A) = FOLLOW(S) = {$}
//         out.clear();
//         nt = std::make_shared<NaoTerminal>("A");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso A\': recursão"){
//         Gramatica g;
//         cria_gram_5(g);

//         // FOLLOW(A') = FOLLOW(A) = FOLLOW(S) = {$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("A\'");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso C: não é usado"){
//         Gramatica g;
//         cria_gram_5(g);

//         // FOLLOW(C) = {} (*conjunto vazio*)
//         std::set<Terminal> conj_follow;

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("C");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso B"){
//         Gramatica g;
//         cria_gram_5(g);

//         // FOLLOW(B) = FIRST(A') U FOLLOW(S) = {d,$}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal("d"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("B");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }

// TEST_CASE("FOLLOW: gramática 6"){
//     SUBCASE("Caso L e L\'"){
//         Gramatica g;
//         cria_gram_6(g);

//         // FOLLOW(L) = {)}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal(")"));

//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("L");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);

//         // FOLLOW(L') = FOLLOW(L) = {)}
//         out.clear();
//         nt = std::make_shared<NaoTerminal>("L\'");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
//     SUBCASE("Caso S"){
//         Gramatica g;
//         cria_gram_6(g);

//         // FOLLOW(S) = {$} U FIRST(L') U FOLLOW(L) U FOLLOW(L') = {$, , ,)}
//         std::set<Terminal> conj_follow;
//         conj_follow.insert(Terminal("$"));
//         conj_follow.insert(Terminal(","));
//         conj_follow.insert(Terminal(")"));


//         std::set<Terminal> out;
//         std::shared_ptr<NaoTerminal> nt = std::make_shared<NaoTerminal>("S");
//         g.follow(nt, out);
//         CHECK(out == conj_follow);
//     }
// }



