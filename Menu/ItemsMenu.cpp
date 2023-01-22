#include "ItemsMenu.hpp"

ItemsMenu::ItemsMenu() : _movingDeltaCord(0, 0), _movingItem(false)
{
	_background.setTexture(Configuration::backgrounds.get(Configuration::Backgrounds::ItemsMenu));
	_background.setPosition(sf::Vector2f(995, 30)); // position items menu
}

void ItemsMenu::processEvent(const sf::Event& event, const sf::Vector2f& mousePos, GameField& gameField, std::vector<std::shared_ptr<Tower>>& towers, Player& player)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
			for (size_t i = 0; i < _items.size(); ++i)
				if (_items[i].getSprite().getGlobalBounds().contains(mousePos)) {
					_movingDeltaCord = sf::Vector2f(mousePos.x - _items[i].getSprite().getPosition().x,
						mousePos.y - _items[i].getSprite().getPosition().y);

					_items.select(i);
					_movingItem = true;
				}
	if (event.type == sf::Event::MouseButtonReleased)
		if (event.key.code == sf::Mouse::Left)
			if (_movingItem) {
				sf::Vector2f temp(mousePos.x - _movingDeltaCord.x, mousePos.y - _movingDeltaCord.y);
				this->placeTower(temp, gameField, towers, player);
				_movingItem = false;
				_items.reset();
			}
}

void ItemsMenu::update(const sf::Vector2f& mousePos)
{
	if (_movingItem)
		_items[_items.size() - 1].getSprite().setPosition(mousePos.x - _movingDeltaCord.x, mousePos.y - _movingDeltaCord.y);
}

void ItemsMenu::render(sf::RenderTarget* target)
{
	target->draw(_background);
	_items.render(target);
}

void ItemsMenu::placeTower(sf::Vector2f& pos, GameField& gameField, std::vector<std::shared_ptr<Tower>>& towers, Player& player)
{
	if (pos.x >= 288 && pos.x <= 928 && pos.y >= -56 && pos.y <= 584) {

		pos.x = (float)(pos.x <= 896 ? (pos.x <= 320 ? 0 : (int)std::round((pos.x - 320) / 64)) : 9) * 64 + 320.f;
		pos.y = (float)(pos.y <= 552 ? (pos.y <= 8 ? 0 : (int)std::round((pos.y - 40 + 64) / 64)) : 9) * 64 - 24.f;

		if (!gameField.isOccupiedCell(pos)) {

			bool isPlaced = false;

			switch (_items[2].getId())
			{
			case 0:
				if (player.getBalance() >= 200) {
					towers.push_back(std::make_shared<Tower>(pos, Configuration::Textures::WoodTower, Configuration::Textures::WoodTower_weapon,
						Configuration::WoodTower_bullet, 20, 200, 4, 200));
					player.changeBalance(-200);
					isPlaced = true;
				}
				break;
			case 1:
				if (player.getBalance() >= 400) {
					towers.push_back(std::make_shared<Tower>(pos, Configuration::Textures::StoneTower, Configuration::Textures::StoneTower_weapon,
						Configuration::Textures::StoneTower_bullet, 50, 300, 3, 400));
					player.changeBalance(-400);
					isPlaced = true;
				}
				break;
			case 2:
				if (player.getBalance() >= 800) {
					towers.push_back(std::make_shared<Tower>(pos, Configuration::Textures::GalacticTower, Configuration::Textures::GalacticTower_weapon,
						Configuration::Textures::GalacticTower_bullet, 120, 350, 2, 800));
					player.changeBalance(-800);
					isPlaced = true;
					gameField.occupyCell(pos);
				}
				break;
			default:
				throw std::exception("[ItemsMenu] - not found tower with id to create");
			}

			if (isPlaced) {
				gameField.occupyCell(sf::Vector2f(pos.x + 1, pos.y + 1));
				for (size_t i = 0; i <= towers.size(); ++i) {
					for (size_t j = 0; j < towers.size() - 1; ++j)
						if (towers[j]->_towerObject.getPosition().y > towers[j + 1]->_towerObject.getPosition().y)
							std::swap(towers[j], towers[j + 1]);
				}
			}
		}
	}
}

