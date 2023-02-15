import xml.etree.ElementTree as ET

class XmlDBParser:
    def __init__(self):
        self.servers = []

    def parse_xml(self, path):
        tree = ET.parse(path)
        root = tree.getroot()
        for child in root:
            if child.tag == 'Server':
                self.servers.append(Server(child))

class Server:
    def __init__(self, node):
        self.token = ''
        self.roles = []
        self.guildId = 0
        self.categories = []
        for child in node:
            if child.tag == 'Token':
                self.token = child.text
            if child.tag == 'GuildId':
                self.guild_id = child.text
            if child.tag == 'Role':
                self.roles.append(Role(child))
            if child.tag == 'Category':
                 self.categories.append(Category(child))

class Role:
    def __init__(self, node):
        self.name = node.attrib['name'].lower()
        self.id = node.text

class Category:
    def __init__(self, node):
        self.name = node.attrib['name'].lower()
        self.id = 0
        self.channels = []
        for child in node:
            if child.tag == 'Id':
                self.id = child.text
            if child.tag == 'Channel':
                self.channels.append(Channel(child))

class Channel:
    def __init__(self, node):
        self.name = node.attrib['name'].lower()
        self.id = node.text
