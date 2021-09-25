require 'rubygems'
require 'algorithms'

def djikstra(matrix, src)
  dist = Array.new(matrix.size, Float::INFINITY)
  prev = Array.new(matrix.size, nil)

  dist[src] = 0

  block = lambda { |x, y| dist[x] < dist[y] }
  h = Containers::MinHeap.new(&block)

  h.push(src)

  while !h.empty?
    u = h.pop
    matrix[u].each_with_index do |len, v|
      next if len.nil?
      alt = dist[u] + len
      if alt < dist[v]
        dist[v] = alt
        prev[v] = u
        h.push(v)
      end
    end
  end
  return [dist, prev]
end

matrix = [
  [nil,2,1,nil],
  [nil,nil,nil,1],
  [nil,nil,3,nil],
  [nil,nil,2,nil]
]
src = 0

dist, prev = djikstra(matrix, src)

raise "Incorrect dist" unless [0, 2, 1, 3] == dist
raise "Incorrect prev" unless [nil, 0, 0, 1] == prev

