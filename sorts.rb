def bubble_sort(arr)
  swapped = true
  while swapped
    swapped = false
    (0...arr.size - 1).each do |i|
      if arr[i] > arr[i+1]
        arr[i], arr[i+1] = arr[i+1], arr[i]
        swapped = true
      end
    end
  end
end

x = [5,3,4,2,1,6]
bubble_sort(x)
puts x.inspect

def selection_sort(arr)
  (0...arr.size).each do |i|
    min_index = i
    (i...arr.size).each do |j|
      if arr[min_index] > arr[j]
        min_index = j
      end
    end
    arr[i], arr[min_index] = arr[min_index], arr[i]
  end
end

x2 = [5,3,4,2,1,6]
selection_sort(x2)
puts x2.inspect

def merge_sort(arr)
  if arr.size <= 1
    return arr
  end
  left = merge_sort(arr[0...arr.size/2])
  right = merge_sort(arr[arr.size/2..])
  return merge(left, right)
end

def merge(left, right)
  output = []
  li, ri = 0, 0
  while li < left.size && ri < right.size
    if left[li] < right[ri]
      output.append(left[li])
      li += 1
    else
      output.append(right[ri])
      ri += 1
    end
  end
  if li < left.size
    output += left[li..]
  elsif ri < right.size
    output += right[ri..]
  end
  return output
end

x3 = [5,3,6,2,1,4]
puts merge_sort(x3).inspect

