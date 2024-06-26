#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

// 복사 생성자
Player::Player(const Player& other)
	: name(other.name), score(other.score), id(other.id), num(other.num)
{
	p = make_unique<char[]>(other.num);
	copy(other.p.get(), other.p.get() + num, p.get());
}

// 복사 대입 연산자.
Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		name = other.name;
		score = other.score;
		id = other.id;
		num = other.num;
		p = std::make_unique<char[]>(other.num);
		std::copy(other.p.get(), other.p.get() + num, p.get());
	}
	return *this;
}

// 이동 생성자
Player::Player(Player&& other) : name(other.name), score(other.score), id(other.id), num(other.num)
{
	p.reset(other.p.get());
	other.p.release();
	other.num = 0;
}

// 이동 할당 연산자
Player& Player::operator=(Player&& other)
{
	if (this != &other)
	{
		name = std::move(other.name);
		score = other.score;
		id = other.id;
		num = other.num;
		p.reset(other.p.release());
		other.num = 0;
	}
	return *this;
}

string Player::getName() const {
	return name;
}

int Player::getScore() const {
	return score;
}

size_t Player::getId() const {
	return id;
}

size_t Player::getNum() const {
	return num;
}

char* Player::getP() const {
	return p.get();
}

bool Player::read(istream& is)
{
	
	is.read((char*)this, sizeof Player);
	p.release();
	p = make_unique<char[]>(num);
	is.read(p.get(), num);

	return bool(is);
}


void Player::show() const {
	cout << "이름: " << name << ", 아이디: " << id << ", 점수: " << score << ", 자원수: " << num << '\n' << "저장된 글자 : " << p << '\n';
}
