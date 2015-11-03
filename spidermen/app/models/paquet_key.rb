class PaquetKey
  include Mongoid::Document
  include Mongoid::Timestamps
  
  field :name, type: String
  field :date, type: String
  field :active, type: String
  field :text, type: String
  field :pid, type: Integer
end
